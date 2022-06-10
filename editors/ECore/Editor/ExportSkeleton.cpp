//----------------------------------------------------
// file: ExportSkeleton.cpp
//----------------------------------------------------
#include "stdafx.h"
#pragma hdrstop

#include "ExportSkeleton.h"
#include "ExportObjectOGF.h"
#include "EditObject.h"
#include "EditMesh.h"
#include "Fmesh.h"
#include "std_classes.h"
#include "bone.h"
#include "motion.h"
#include "Library.h"

#include "MgcCont3DBox.h"         
#include "MgcCont3DMinBox.h"         

#include "ui_main.h"
#include "UI_ToolsCustom.h"
#include "SkeletonAnimated.h"

#include "../../common/NvMender2003/NVMeshMender.h"
#include "../../common/NvMender2003/mender_input_output.h"
#include "../../common/NvMender2003/remove_isolated_verts.h"

IC void	set_vertex( MeshMender::Vertex &out_vertex, const SSkelVert& in_vertex )
{
			cv_vector( out_vertex.pos,		in_vertex.offs );
			cv_vector( out_vertex.normal,	in_vertex.norm );
			out_vertex.s		= in_vertex.uv.x;
			out_vertex.t		= in_vertex.uv.y;
			//out_vertex.tangent;
			//out_vertex.binormal;
}

IC void	set_vertex( SSkelVert& out_vertex,  const SSkelVert& in_old_vertex, const MeshMender::Vertex &in_vertex )
{
			out_vertex = in_old_vertex;

			cv_vector( out_vertex.offs, in_vertex.pos );//?
			cv_vector( out_vertex.norm, in_vertex.normal );//?

			out_vertex.uv.x	= in_vertex.s;
			out_vertex.uv.y	= in_vertex.t;
			Fvector tangent; Fvector binormal;
			out_vertex.tang.set( cv_vector( tangent, in_vertex.tangent ) );
			out_vertex.binorm.set( cv_vector( binormal, in_vertex.binormal ) );
}


IC u16	&face_vertex( SSkelFace &F, u32 vertex_index )
{
	VERIFY( vertex_index < 3 );
	return F.v[vertex_index];
}

IC const u16 &face_vertex( const SSkelFace &F, u32 vertex_index )
{
	VERIFY( vertex_index < 3 );
	return F.v[vertex_index];
}

ECORE_API BOOL g_force16BitTransformQuant = FALSE;

u16 CSkeletonCollectorPacked::VPack(SSkelVert& V)
{
    u32 P 	= 0xffffffff;

    u32 ix,iy,iz;
    ix = iFloor(float(V.offs.x-m_VMmin.x)/m_VMscale.x*clpSMX);
    iy = iFloor(float(V.offs.y-m_VMmin.y)/m_VMscale.y*clpSMY);
    iz = iFloor(float(V.offs.z-m_VMmin.z)/m_VMscale.z*clpSMZ);
    R_ASSERT(ix<=clpSMX && iy<=clpSMY && iz<=clpSMZ);

	int similar_pos=-1;
    {
        U32Vec& vl=m_VM[ix][iy][iz];
        for(U32It it=vl.begin();it!=vl.end(); it++){
        	SSkelVert& src=m_Verts[*it];
        	if(src.similar_pos(V)){
	            if(src.similar(V)){
                    P = *it;
                    break;
            	}
                similar_pos=*it;
            }
        }
    }
    if (0xffffffff==P)
    {
    	if (similar_pos>=0) V.offs.set(m_Verts[similar_pos].offs);
        P = m_Verts.size();
        m_Verts.push_back(V);

        m_VM[ix][iy][iz].push_back(P);

        u32 ixE,iyE,izE;
        ixE = iFloor(float(V.offs.x+m_VMeps.x-m_VMmin.x)/m_VMscale.x*clpSMX);
        iyE = iFloor(float(V.offs.y+m_VMeps.y-m_VMmin.y)/m_VMscale.y*clpSMY);
        izE = iFloor(float(V.offs.z+m_VMeps.z-m_VMmin.z)/m_VMscale.z*clpSMZ);

        R_ASSERT(ixE<=clpSMX && iyE<=clpSMY && izE<=clpSMZ);

        if (ixE!=ix)							m_VM[ixE][iy][iz].push_back	(P);
        if (iyE!=iy)							m_VM[ix][iyE][iz].push_back	(P);
        if (izE!=iz)							m_VM[ix][iy][izE].push_back	(P);
        if ((ixE!=ix)&&(iyE!=iy))				m_VM[ixE][iyE][iz].push_back(P);
        if ((ixE!=ix)&&(izE!=iz))				m_VM[ixE][iy][izE].push_back(P);
        if ((iyE!=iy)&&(izE!=iz))				m_VM[ix][iyE][izE].push_back(P);
        if ((ixE!=ix)&&(iyE!=iy)&&(izE!=iz))	m_VM[ixE][iyE][izE].push_back(P);
    }
    VERIFY	(P<u16(-1));
    return 	(u16)P;
}

CSkeletonCollectorPacked::CSkeletonCollectorPacked(const Fbox &_bb, int apx_vertices, int apx_faces)
{
	Fbox bb;		bb.set(_bb); bb.grow(EPS_L);
    // Params
    m_VMscale.set	(bb.max.x-bb.min.x+EPS, bb.max.y-bb.min.y+EPS, bb.max.z-bb.min.z+EPS);
    m_VMmin.set		(bb.min).sub(EPS);
    m_VMeps.set		(m_VMscale.x/clpSMX/2,m_VMscale.y/clpSMY/2,m_VMscale.z/clpSMZ/2);
    m_VMeps.x		= (m_VMeps.x<EPS_L)?m_VMeps.x:EPS_L;
    m_VMeps.y		= (m_VMeps.y<EPS_L)?m_VMeps.y:EPS_L;
    m_VMeps.z		= (m_VMeps.z<EPS_L)?m_VMeps.z:EPS_L;

    invalid_faces	= 0;

    // Preallocate memory
    m_Verts.reserve	(apx_vertices);
    m_Faces.reserve	(apx_faces);

    int		_size	= (clpSMX+1)*(clpSMY+1)*(clpSMZ+1);
    int		_average= (apx_vertices/_size)/2;
    for (int ix=0; ix<clpSMX+1; ix++)
        for (int iy=0; iy<clpSMY+1; iy++)
            for (int iz=0; iz<clpSMZ+1; iz++)
                m_VM[ix][iy][iz].reserve	(_average);
}
//----------------------------------------------------

CExportSkeleton::SSplit::SSplit(CSurface* surf, const Fbox& bb, u16 part):CSkeletonCollectorPacked(bb)
{
	m_b2Link	= FALSE;
    m_Shader	= surf->m_ShaderName;
    m_Texture	= surf->m_Texture;
    m_PartID 	= part;
}
//----------------------------------------------------




class VertexCache
{

public:
	VertexCache		(int size);
	VertexCache		();
	~VertexCache	();

	bool			InCache	(int entry);
	int				AddEntry(int entry);
	void			Clear	();

	void			Copy	(VertexCache* inVcache);
	int				At		(int index);
	void			Set		(int index, int value);

private:
	xr_vector<int>	entries;
};

IC bool VertexCache::InCache(int entry)
{
	bool returnVal = false;

	for(u32 i = 0; i < entries.size(); i++)
	{
		if(entries[i] == entry)
		{
			returnVal = true;
			break;
		}
	}

	return returnVal;
}


IC int VertexCache::AddEntry(int entry)
{
	int removed;

	removed = entries[entries.size() - 1];

	//push everything right one
	for(int i = (u32)entries.size() - 2; i >= 0; i--)
	{
		entries[i + 1] = entries[i];
	}

	entries[0] = entry;

	return removed;
}

VertexCache::VertexCache()
{
  VertexCache(24);
}


VertexCache::VertexCache(int size)
{
	entries.assign	(size,-1);
}


VertexCache::~VertexCache()
{
	entries.clear	();
}


int VertexCache::At	(int index)
{
  return entries[index];
}

void VertexCache::Set(int index, int value)
{
	entries[index] = value;
}


void VertexCache::Clear()
{
	for(u32 i = 0; i < entries.size(); i++)
		entries[i] = -1;
}

void VertexCache::Copy(VertexCache* inVcache)
{
	for(u32 i = 0; i < entries.size(); i++)
	{
		inVcache->Set(i, entries[i]);
	}
}

int xrSimulate (u16* indices, u32 i_cnt, int iCacheSize )
{
	VertexCache C(iCacheSize);

	int count=0;
	for (u32 i=0; i<i_cnt; i++)
	{
		int id = indices[i];
		if (C.InCache(id)) continue;
		count++;
		C.AddEntry(id);
	}
	return count;
}



static	D3DVERTEXELEMENT9 dwDecl_NW	[] =	// 32bytes
{
	{ 0, 0,		D3DDECLTYPE_SHORT4,		D3DDECLMETHOD_DEFAULT, 	D3DDECLUSAGE_POSITION,		0 },	// : p,		w =	influence	: 2	: -12..+12
	{ 0, 8,		D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, 	D3DDECLUSAGE_NORMAL,		0 },	// : n.xyz					: 1	:  -1..+1, w=0..1
	{ 0, 12,	D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, 	D3DDECLUSAGE_TANGENT,		0 },	// : T						: 1	:  -1..+1
	{ 0, 16,	D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, 	D3DDECLUSAGE_BINORMAL,		0 },	// : B						: 1	:  -1..+1
	{ 0, 20,	D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, 	D3DDECLUSAGE_COLOR ,		0 },	// : bones					: 1	:  -1..+1
	{ 0, 24,	D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, 	D3DDECLUSAGE_COLOR ,		1 },	// : weights				: 1	:  -1..+1
	{ 0, 28,	D3DDECLTYPE_SHORT2,		D3DDECLMETHOD_DEFAULT, 	D3DDECLUSAGE_TEXCOORD,		0 },	// : xy(tc)					: 2	: -16..+16, zw[0..32767]
	D3DDECL_END()
};


void CExportSkeleton::SSplit::Save(IWriter& F)
{
    // Header
    F.open_chunk		(OGF_HEADER);
    ogf_header			H;
    H.format_version	= xrOGF_FormatVersion;
    H.type				= (m_SWR.size())?MT_SKELETON_GEOMDEF_PM:MT_SKELETON_GEOMDEF_ST;
    H.shader_id			= 0;
    H.bb.min			= m_Box.min;
    H.bb.max			= m_Box.max;                    
    m_Box.getsphere		(H.bs.c,H.bs.r);
    F.w					(&H,sizeof(H));
    F.close_chunk		();
    
    // Texture
    F.open_chunk		(OGF_TEXTURE);
    F.w_stringZ			(m_Texture);
    F.w_stringZ			(m_Shader);
    F.close_chunk		();

    // Vertices
    F.open_chunk		(OGF_VERTICES);
    F.w_u32				(m_b2Link?OGF_VERTEXFORMAT_FVF_2L:OGF_VERTEXFORMAT_FVF_1L);
    F.w_u32				(m_Verts.size());
    if (m_b2Link){
        for (SkelVertIt v_it=m_Verts.begin(); v_it!=m_Verts.end(); v_it++){
            SSkelVert& pV 	= *v_it;
            pV.sort_by_weight	();
			// write vertex
            F.w_u16		(pV.bones[0].id);
            F.w_u16		(pV.bones[1].id);
            F.w			(&pV.offs,sizeof(Fvector));		// position (offset)
            F.w			(&pV.norm,sizeof(Fvector));		// normal
            F.w			(&pV.tang,sizeof(Fvector));		// T        
            F.w			(&pV.binorm,sizeof(Fvector));	// B        
            F.w_float	(pV.bones[1].w/(pV.bones[0].w+pV.bones[1].w));	// SV.w	= wb[1].weight/(wb[0].weight+wb[1].weight);
            F.w			(&pV.uv,sizeof(Fvector2));		// tu,tv
        }
    }else{
        for (SkelVertIt v_it=m_Verts.begin(); v_it!=m_Verts.end(); v_it++){
            SSkelVert& pV 	= *v_it;
            pV.sort_by_weight	();
            F.w			(&pV.offs,sizeof(Fvector));		// position (offset)
            F.w			(&pV.norm,sizeof(Fvector));		// normal
            F.w			(&pV.tang,sizeof(Fvector));		// T        
            F.w			(&pV.binorm,sizeof(Fvector));	// B        
            F.w			(&pV.uv,sizeof(Fvector2));		// tu,tv
            F.w_u32		(pV.bones[0].id); 
        }
    }
    F.close_chunk		();

    // Faces
    F.open_chunk		(OGF_INDICES);
    F.w_u32				(m_Faces.size()*3);
    F.w					(m_Faces.begin(),m_Faces.size()*3*sizeof(WORD));
    F.close_chunk		();

    // PMap
    if (m_SWR.size()) {
        F.open_chunk(OGF_SWIDATA);
        F.w_u32			(0);			// reserved space 16 bytes
        F.w_u32			(0);
        F.w_u32			(0);
        F.w_u32			(0);
        F.w_u32			(m_SWR.size()); // num collapses
        for (u32 swr_idx=0; swr_idx<m_SWR.size(); swr_idx++)
        	F.w			(&m_SWR[swr_idx],sizeof(VIPM_SWR));
        F.close_chunk();
    }
// SMF
/*
	if (0){
    	static u32 chunk_id = 0; chunk_id++;
		AnsiString r=AnsiString("x:\\import\\test")+chunk_id+".smf";
        IWriter* W 	= FS._w_open(r.c_str());
        for (SkelVertIt v_it=m_Verts.begin(); v_it!=m_Verts.end(); v_it++){
            SSkelVert& pV 	= *v_it;
			// vertices
            AnsiString 		tmp;
            tmp.sprintf		("v %f %f %f",pV.O.x,pV.O.y,-pV.O.z);
            W->w_string		(tmp.c_str());
        }
        // face
        for (SkelFaceIt f_it=m_Faces.begin(); f_it!=m_Faces.end(); f_it++){
            SSkelFace& pF 	= *f_it;
            AnsiString 		tmp;
            tmp.sprintf		("f %d %d %d",pF.v[0]+1,pF.v[2]+1,pF.v[1]+1);
            W->w_string		(tmp.c_str());
        }
        // normals
        W->w_string			("bind n vertex");
        for (v_it=m_Verts.begin(); v_it!=m_Verts.end(); v_it++){
            SSkelVert& pV 	= *v_it;
            AnsiString 		tmp;
            tmp.sprintf		("n %f %f %f",pV.N.x,pV.N.y,-pV.N.z);
            W->w_string		(tmp.c_str());
        }
        FS.w_close	(W);
	}
*/    
}

void CExportSkeleton::SSplit::CalculateTB()
{
	xr_vector<MeshMender::Vertex>	mender_in_out_verts;
	xr_vector< unsigned int >		mender_in_out_indices;
	xr_vector< unsigned int >		mender_mapping_out_to_in_vert;

	fill_mender_input( m_Verts, m_Faces, mender_in_out_verts, mender_in_out_indices );

	MeshMender	mender	;
	if
	(
		!mender.Mend
		(
		  mender_in_out_verts,
		  mender_in_out_indices,
		  mender_mapping_out_to_in_vert,
		  1,
		  0.5,
		  0.5,
		  0.0f,
		  MeshMender::DONT_CALCULATE_NORMALS,
		  MeshMender::RESPECT_SPLITS,
		  MeshMender::DONT_FIX_CYLINDRICAL
		)
	)
	{
		Debug.fatal	( DEBUG_INFO, "NVMeshMender failed " );
		//Debug.fatal	(DEBUG_INFO,"NVMeshMender failed (%s)",mender.GetLastError().c_str());
	}

	retrive_data_from_mender_otput( m_Verts, m_Faces, mender_in_out_verts, mender_in_out_indices, mender_mapping_out_to_in_vert  );

	t_remove_isolated_verts( m_Verts, m_Faces );

	mender_in_out_verts				.clear( );
	mender_in_out_indices			.clear( );
	mender_mapping_out_to_in_vert	.clear( );



    // Optimize texture coordinates
    // 1. Calc bounds
	u32	v_cnt	= m_Verts.size();
    u32 v_idx		= 0;
    Fvector2 	Tdelta;
    Fvector2 	Tmin,Tmax;
    Tmin.set	(flt_max,flt_max);
    Tmax.set	(flt_min,flt_min);
    for (v_idx=0; v_idx!=v_cnt; v_idx++){
        SSkelVert	&iV = m_Verts[v_idx];
        Tmin.min	(iV.uv);
        Tmax.max	(iV.uv);
    }
    Tdelta.x 	= floorf((Tmax.x-Tmin.x)/2+Tmin.x);
    Tdelta.y 	= floorf((Tmax.y-Tmin.y)/2+Tmin.y);

    Fvector2	Tsize;
    Tsize.sub	(Tmax,Tmin);
    if ((Tsize.x>32)||(Tsize.y>32))
    	Msg		("#!Surface [T:'%s', S:'%s'] has UV tiled more than 32 times.",*m_Texture,*m_Shader);
    
    // 2. Recalc UV mapping
    for (v_idx=0; v_idx!=v_cnt; v_idx++){
        SSkelVert	&iV = m_Verts[v_idx];
        iV.uv.sub	(Tdelta);
    }
}

void CExportSkeleton::SSplit::MakeProgressive()
{
	VIPM_Init	();
    for (SkelVertIt vert_it=m_Verts.begin(); vert_it!=m_Verts.end(); vert_it++)
    	VIPM_AppendVertex(vert_it->offs,vert_it->uv);
    for (SkelFaceIt f_it=m_Faces.begin(); f_it!=m_Faces.end(); f_it++)
    	VIPM_AppendFace(f_it->v[0],f_it->v[1],f_it->v[2]);       

    VIPM_Result* R = VIPM_Convert(u32(-1),1.f,1);

    if (R){
        // Permute vertices
        SkelVertVec temp_list = m_Verts;
        for(u32 i=0; i<temp_list.size(); i++)
            m_Verts[R->permute_verts[i]]=temp_list[i];
    
        // Fill indices
        m_Faces.resize	(R->indices.size()/3);
        for (u32 f_idx=0; f_idx<m_Faces.size(); f_idx++){
            SSkelFace& F= m_Faces[f_idx];
            F.v[0]			= R->indices[f_idx*3+0];
            F.v[1]			= R->indices[f_idx*3+1];
            F.v[2]			= R->indices[f_idx*3+2];
        }

        // Fill SWR
        m_SWR.resize		(R->swr_records.size());
        for (u32 swr_idx=0; swr_idx!=m_SWR.size(); swr_idx++)
            m_SWR[swr_idx]	= R->swr_records[swr_idx];
	}else{
    	Log("!..Can't make progressive.");
    }
    
    // cleanup
    VIPM_Destroy		();
}

void CExportSkeleton::SSplit::MakeStripify()
{
//	int ccc 	= xrSimulate	((u16*)&m_Faces.front(),m_Faces.size()*3,24);        
//	Log("SRC:",ccc);
	// alternative stripification - faces
    {
        DWORD*		remap	= xr_alloc<DWORD>		(m_Faces.size());
        HRESULT		rhr		= D3DXOptimizeFaces		(&m_Faces.front(),m_Faces.size(),m_Verts.size(),FALSE,remap);
        R_CHK		(rhr);
        SkelFaceVec	_source	= m_Faces;
        for (u32 it=0; it<_source.size(); it++)		m_Faces[it] = _source[remap[it]];  
        xr_free		(remap);
        
//	    int ccc 	= xrSimulate	((u16*)&m_Faces.front(),m_Faces.size()*3,24);
//		Log("X:",ccc);
    }
    // alternative stripification - vertices
    {
        DWORD*		remap	= xr_alloc<DWORD>		(m_Verts.size());
        HRESULT		rhr		= D3DXOptimizeVertices	(&m_Faces.front(),m_Faces.size(),m_Verts.size(),FALSE,remap);
        R_CHK		(rhr);
        SkelVertVec	_source = m_Verts;
        for(u32 vit=0; vit<_source.size(); vit++)	m_Verts[remap[vit]]		= _source[vit];     
        for(u32 fit=0; fit<m_Faces.size(); fit++)	for (u32 j=0; j<3; j++)	m_Faces[fit].v[j]= remap[m_Faces[fit].v[j]];
        xr_free		(remap);

//	    int ccc 	= xrSimulate	((u16*)&m_Faces.front(),m_Faces.size()*3,24);
//		Log("Y:",ccc);
    }
}

/*
    // write SMF
    AnsiString r		= "x:\\import\\test.smf";
    IWriter* W 			= FS._w_open(r.c_str());
    // vertices
    for (SkelVertIt v_it=m_Verts.begin(); v_it!=m_Verts.end(); v_it++){
        SSkelVert& pV 	= *v_it;
        AnsiString 		tmp;
        tmp.sprintf		("v %f %f %f",pV.O.x,pV.O.y,-pV.O.z);
        W->w_string		(tmp.c_str());
    }
    u32 idx 			= R->swr_records.size()-1;
    VIPM_SWR& swr		= R->swr_records[idx];
    for (f_idx=0; f_idx<swr.num_tris; f_idx++){
	    SSkelFace& F	= m_Faces[f_idx+swr.offset/3];

		u16* idx		= &R->indices[swr.offset+f_idx*3];
	    SSkelFace F0;
        F0.v[0]			= *(idx+0);
        F0.v[1]			= *(idx+1);
        F0.v[2]			= *(idx+2);

        AnsiString 		tmp;
        tmp.sprintf		("f %d %d %d",F.v[2]+1,F.v[1]+1,F.v[0]+1);
		W->w_string		(tmp.c_str());
    }
    FS.w_close	(W);
*/

CExportSkeleton::CExportSkeleton(CEditableObject* object)
{
	m_Source=object;
}
//----------------------------------------------------
#include "WmlMath.h"
#include "WmlContMinBox3.h"
#include "WmlContBox3.h"

extern BOOL RAPIDMinBox(Fobb& B, Fvector* vertices, u32 v_count);
void ComputeOBB_RAPID	(Fobb &B, FvectorVec& V, u32 t_cnt)
{
	VERIFY	(t_cnt==(V.size()/3));
    if ((t_cnt<1)||(V.size()<3)) { B.invalidate(); return; }
    RAPIDMinBox			(B,V.begin(),V.size());

    // Normalize rotation matrix (???? ???????? ContOrientedBox - ?????? ????? ???????)
    B.m_rotate.i.crossproduct(B.m_rotate.j,B.m_rotate.k);
    B.m_rotate.j.crossproduct(B.m_rotate.k,B.m_rotate.i);
    
    VERIFY (_valid(B.m_rotate)&&_valid(B.m_translate)&&_valid(B.m_halfsize));
}

void ComputeOBB_WML		(Fobb &B, FvectorVec& V)
{
    if (V.size()<3) { B.invalidate(); return; }
    float 	HV				= flt_max;
    {
        Wml::Box3<float> 	BOX;
        Wml::MinBox3<float> mb(V.size(), (const Wml::Vector3<float>*) V.begin(), BOX);
        float hv			= BOX.Extents()[0]*BOX.Extents()[1]*BOX.Extents()[2];
        if (hv<HV){
        	HV 				= hv;
            B.m_rotate.i.set(BOX.Axis(0));
            B.m_rotate.j.set(BOX.Axis(1));
            B.m_rotate.k.set(BOX.Axis(2));

            B.m_translate.set(BOX.Center());
            B.m_halfsize.set(BOX.Extents()[0],BOX.Extents()[1],BOX.Extents()[2]);
        }
    }
/*    
    // ??????? 2
    {
        Wml::Box3<float> BOX= Wml::ContOrientedBox(V.size(), (const Wml::Vector3<float>*) V.begin());
        float hv			= BOX.Extents()[0]*BOX.Extents()[1]*BOX.Extents()[2];
        if (hv<HV){
        	HV 				= hv;
            B.m_rotate.i.set(BOX.Axis(0));
            B.m_rotate.j.set(BOX.Axis(1));
            B.m_rotate.k.set(BOX.Axis(2));

            B.m_translate.set(BOX.Center());
            B.m_halfsize.set(BOX.Extents()[0],BOX.Extents()[1],BOX.Extents()[2]);
        }
    }
    // ??????? 3
    {
        Mgc::Box3	BOX		= Mgc::ContOrientedBox(V.size(), (const Mgc::Vector3*) V.begin());
        float hv			= BOX.Extents()[0]*BOX.Extents()[1]*BOX.Extents()[2];
        if (hv<HV){
        	HV 				= hv;
            B.m_rotate.i.set(BOX.Axis(0));
            B.m_rotate.j.set(BOX.Axis(1));
            B.m_rotate.k.set(BOX.Axis(2));
    
            B.m_translate.set(BOX.Center());
            B.m_halfsize.set(BOX.Extents()[0],BOX.Extents()[1],BOX.Extents()[2]);
        }
    }
    // ??????? 4
    {
        Mgc::Box3	BOX		= Mgc::MinBox(V.size(), (const Mgc::Vector3*) V.begin());
        float hv			= BOX.Extents()[0]*BOX.Extents()[1]*BOX.Extents()[2];
        if (hv<HV){
        	HV 				= hv;
            B.m_rotate.i.set(BOX.Axis(0));
            B.m_rotate.j.set(BOX.Axis(1));
            B.m_rotate.k.set(BOX.Axis(2));

            B.m_translate.set(BOX.Center());
            B.m_halfsize.set(BOX.Extents()[0],BOX.Extents()[1],BOX.Extents()[2]);
        }
    }
*/
    // Normalize rotation matrix (???? ???????? ContOrientedBox - ?????? ????? ???????)
    B.m_rotate.i.crossproduct(B.m_rotate.j,B.m_rotate.k);
    B.m_rotate.j.crossproduct(B.m_rotate.k,B.m_rotate.i);
    
    VERIFY (_valid(B.m_rotate)&&_valid(B.m_translate)&&_valid(B.m_halfsize));
}
//----------------------------------------------------

int CExportSkeletonCustom::FindSplit(shared_str shader, shared_str texture, u16 part_id)
{
	for (SplitIt it=m_Splits.begin(); it!=m_Splits.end(); it++)
		if (it->m_Shader.equal(shader)&&it->m_Texture.equal(texture)&&(it->m_PartID==part_id)) return it-m_Splits.begin();
    return -1;
}
//----------------------------------------------------

IC void BuildGroups(CBone* B, U16Vec& tgt, u16 id, u16& last_id)
{
    if (B->IK_data.ik_flags.is(SJointIKData::flBreakable)) id = ++last_id;
	tgt[B->SelfID]	= id;
    for (BoneIt bone_it=B->children.begin(); bone_it!=B->children.end(); bone_it++)
    	BuildGroups	(*bone_it,tgt,id,last_id);
}

bool CExportSkeleton::PrepareGeometry(u8 influence)
{
    if( m_Source->MeshCount() == 0 ) return false;

    if (m_Source->BoneCount()<1){
    	ELog.Msg(mtError,"There are no bones in the object.");
     	return false;
    }

    if (m_Source->BoneCount()>64){
    	ELog.Msg(mtError,"Object cannot handle more than 64 bones.");
     	return false;
    }

    // mem active motion
    CSMotion* active_motion=m_Source->ResetSAnimation();

    R_ASSERT(m_Source->IsDynamic()&&m_Source->IsSkeleton());

    SPBItem* pb = UI->ProgressStart(5+m_Source->MeshCount()*2+m_Source->SurfaceCount(),"..Prepare skeleton geometry");
    pb->Inc		();

    bool bBreakable		= false;
    U16Vec   			bone_brk_parts(m_Source->BoneCount());
    CBone* root 		= 0;
    for (BoneIt bone_it=m_Source->FirstBone(); bone_it!=m_Source->LastBone(); bone_it++){
	    CBone* B 		= *bone_it;
    	if (B->IK_data.ik_flags.is(SJointIKData::flBreakable))	bBreakable 	= true;
    	if (B->IsRoot()) 										root 		= B;
    }
    if (bBreakable){
    	VERIFY 			(root);
        u16 last_id		= 0;
		BuildGroups    	(root,bone_brk_parts,0,last_id);
    }
//*
	for (U16It uit=bone_brk_parts.begin(); uit!=bone_brk_parts.end(); uit++){
    	Msg				("Bone: %s - Part: %d",*m_Source->GetBone(uit-bone_brk_parts.begin())->Name(),*uit);
    }
//*/    
    bool bRes			= true;
	UI->SetStatus("..Split meshes");
    U16Vec				tmp_bone_list;
    for(EditMeshIt mesh_it=m_Source->FirstMesh();mesh_it!=m_Source->LastMesh();mesh_it++){
    	if (!bRes)		break;
        CEditableMesh* MESH = *mesh_it;
        // generate vertex offset
        MESH->GenerateVNormals();
        MESH->GenerateFNormals();
        MESH->GenerateSVertices(influence);
        pb->Inc		();
        // fill faces
        for (SurfFacesPairIt sp_it=MESH->m_SurfFaces.begin(); sp_it!=MESH->m_SurfFaces.end(); sp_it++){
	    	if (!bRes)	break;
            IntVec& face_lst = sp_it->second;
            CSurface* surf = sp_it->first;
            u32 dwTexCnt = ((surf->_FVF()&D3DFVF_TEXCOUNT_MASK)>>D3DFVF_TEXCOUNT_SHIFT);
            R_ASSERT(dwTexCnt==1);
            for (IntIt f_it=face_lst.begin(); f_it!=face_lst.end(); f_it++){
		    	if (!bRes)break;
            	int f_idx = *f_it;
                // case 2 links
                if (influence<=2){
                	BOOL b2Link	= FALSE;
                    SSkelVert v[3];
					tmp_bone_list.clear_not_free();
                    for (int k=0; k<3; k++){
                        st_SVert& 		sv 	= MESH->m_SVertices[f_idx*3+k];
                        VERIFY			(sv.bones.size()>0 && (u8)sv.bones.size()<=influence);
                        if (sv.bones.size()==1){
                        	st_SVert::bone b[2];
                            b[0].id	= b[1].id = sv.bones[0].id;
                            b[0].w	= 1.f;
                            b[1].w	= 0.f;
                            v[k].set		(sv.offs,sv.norm,sv.uv,2,b); 
                            tmp_bone_list.push_back	(sv.bones[0].id);
                        }else{            
                        	if (fsimilar(sv.bones[1].w,0.f,EPS_L)){
                                v[k].set	(sv.offs,sv.norm,sv.uv,(u8)sv.bones.size(),sv.bones.begin());
	                            tmp_bone_list.push_back	(sv.bones[0].id);
                            }else if (fsimilar(sv.bones[0].w,0.f,EPS_L)){
                            	std::swap	(sv.bones[0],sv.bones[1]);
                                v[k].set	(sv.offs,sv.norm,sv.uv,(u8)sv.bones.size(),sv.bones.begin());
	                            tmp_bone_list.push_back	(sv.bones[1].id);
                            }else{
                            	b2Link		= TRUE;
                                v[k].set	(sv.offs,sv.norm,sv.uv,(u8)sv.bones.size(),sv.bones.begin());
                                tmp_bone_list.push_back	(sv.bones[0].id);
                                tmp_bone_list.push_back	(sv.bones[1].id);
                            }
                        }
                    }
                    u16 bone_brk_part		= 0;
                    if (bBreakable){
                        std::sort			(tmp_bone_list.begin(),tmp_bone_list.end());
                        U16It ne			= std::unique(tmp_bone_list.begin(),tmp_bone_list.end());
                        tmp_bone_list.erase	(ne,tmp_bone_list.end());
                        U16It tit			= tmp_bone_list.begin();
                        bone_brk_part		= bone_brk_parts[*tit]; tit++;
                        for (; tit!=tmp_bone_list.end(); tit++)
                        	if (bone_brk_part!=bone_brk_parts[*tit]){
                                ELog.Msg	(mtError,"Can't export object as breakable. Object have N-Link face(s).");
                                bRes		= false;
                            }                    	
                    }
                    // find split
                    int mtl_idx 	= FindSplit(surf->m_ShaderName,surf->m_Texture,bone_brk_part);
                    if (mtl_idx<0){
                        m_Splits.push_back(SSplit(surf,m_Source->GetBox(),bone_brk_part));
                        mtl_idx		= m_Splits.size()-1;
                    }
                    SSplit& split	= m_Splits[mtl_idx];
					if (b2Link)	split.m_b2Link 	= TRUE;
//					split.m_b2Link 	= b2Link;
                    split.m_UsedBones.insert(split.m_UsedBones.end(),tmp_bone_list.begin(),tmp_bone_list.end());
                    // append face
                    split.add_face(v[0], v[1], v[2]);
			        if (surf->m_Flags.is(CSurface::sf2Sided)){
                    	v[0].norm.invert(); v[1].norm.invert(); v[2].norm.invert();
                    	split.add_face	(v[0], v[2], v[1]);
                    }
                }
            }
        }
        // mesh fin
        MESH->UnloadSVertices();
        MESH->UnloadVNormals();
        MESH->UnloadFNormals();
        pb->Inc		();
    }
    UI->SetStatus	("..Calculate TB");

    // check splits
    if (bRes){
        Msg				("Split statistic:");
        for (int k=0; k<(int)m_Splits.size(); k++){
            if (!m_Splits[k].valid()){
                ELog.Msg		(mtError,"Empty split found (Shader/Texture: %s/%s). Removed.",*m_Splits[k].m_Shader,*m_Splits[k].m_Texture);
                m_Splits.erase	(m_Splits.begin()+k); k--;
            }else{
                SSplit& split	= m_Splits[k];
                std::sort		(split.m_UsedBones.begin(),split.m_UsedBones.end());
                U16It ne		= std::unique(split.m_UsedBones.begin(),split.m_UsedBones.end());
                split.m_UsedBones.erase	(ne,split.m_UsedBones.end());
                Msg				(" - Split %d: [Bones: %d, Links: %d, Faces: %d, Verts: %d, BrPart: %d, Shader/Texture: '%s'/'%s']",k,split.m_UsedBones.size(),split.m_b2Link?2:1,split.getTS(),split.getVS(),split.m_PartID,*m_Splits[k].m_Shader,*m_Splits[k].m_Texture);
            }
        }
        // calculate TB
        for (SplitIt split_it=m_Splits.begin(); split_it!=m_Splits.end(); split_it++){
            split_it->CalculateTB();
            pb->Inc		();
        }
        pb->Inc			();
        // compute bounding
        ComputeBounding	();
    }
    UI->ProgressEnd(pb);

    // restore active motion       6
    m_Source->SetActiveSMotion(active_motion);

    return bRes;
}

bool CExportSkeleton::ExportAsSimple(IWriter& F)
{
	if (!PrepareGeometry(2)) return false;
    {
        // Saving geometry...
        if ( m_Splits.size()==1 )
        {
            // export as single mesh
            m_Splits[0].Save(F);
            return true;
        } else
        return false;
    }

}

#define _string_lod

bool CExportSkeleton::ExportGeometry(IWriter& F, u8 infl)
{
	if (!PrepareGeometry(infl)) return false;

    SPBItem* pb = UI->ProgressStart(3+m_Splits.size(),"..Export skeleton geometry");
    pb->Inc		("Make Progressive...");
    // fill per bone vertices
    BoneVec& bones 			= m_Source->Bones();
    xr_vector<FvectorVec>	bone_points;
	bone_points.resize		(m_Source->BoneCount());

    for (SplitIt split_it=m_Splits.begin(); split_it!=m_Splits.end(); split_it++){
		if (m_Source->m_Flags.is(CEditableObject::eoProgressive)) 	split_it->MakeProgressive();
        else														split_it->MakeStripify();
		SkelVertVec& lst = split_it->getV_Verts();
	    for (SkelVertIt sv_it=lst.begin(); sv_it!=lst.end(); sv_it++){
		    bone_points		[sv_it->bones[0].id].push_back						(sv_it->offs);
            bones			[sv_it->bones[0].id]->_RITransform().transform_tiny(bone_points[sv_it->bones[0].id].back());
        }
        pb->Inc		();
    }

	// create OGF
    // Header
    ogf_header 		H;
    H.format_version= xrOGF_FormatVersion;
    H.type			= m_Source->IsAnimated()?MT_SKELETON_ANIM:MT_SKELETON_RIGID;
    H.shader_id		= 0;
    H.bb.min		= m_Box.min;
    H.bb.max		= m_Box.max;
    m_Box.getsphere	(H.bs.c,H.bs.r);
    F.w_chunk		(OGF_HEADER,&H,sizeof(H));

    // Desc
    ogf_desc		desc;
    m_Source->PrepareOGFDesc(desc);
    F.open_chunk	(OGF_S_DESC);
    desc.Save		(F);
    F.close_chunk	();

    // OGF_CHILDREN
    F.open_chunk	(OGF_CHILDREN);
    int chield=0;
    for (split_it=m_Splits.begin(); split_it!=m_Splits.end(); split_it++){
	    F.open_chunk(chield++);
        split_it->Save(F);
	    F.close_chunk();
    }
    F.close_chunk();

    pb->Inc		("Compute bone bounding volume...");

    // BoneNames
    F.open_chunk(OGF_S_BONE_NAMES);
    F.w_u32(m_Source->BoneCount());
    int bone_idx=0;
    for (BoneIt bone_it=m_Source->FirstBone(); bone_it!=m_Source->LastBone(); bone_it++,bone_idx++){
        F.w_stringZ	((*bone_it)->Name());
		F.w_stringZ	((*bone_it)->Parent()?(*bone_it)->ParentName().c_str():"");
        Fobb	obb;
        ComputeOBB_WML	(obb,bone_points[bone_idx]);
        F.w				(&obb,sizeof(Fobb));
    }
    F.close_chunk();

    bool bRes = true;
                    
    F.open_chunk(OGF_S_IKDATA);
    for (bone_it=m_Source->FirstBone(); bone_it!=m_Source->LastBone(); bone_it++,bone_idx++)
        if (!(*bone_it)->ExportOGF(F)) bRes=false; 
    F.close_chunk();

    if (m_Source->GetClassScript().size()){
        F.open_chunk	(OGF_S_USERDATA);
        F.w_stringZ		(m_Source->GetClassScript());
        F.close_chunk	();
    }

    pb->Inc		();

    if (m_Source->GetLODs() && xr_strlen(m_Source->GetLODs())>0 && bRes)
    {
        F.open_chunk	(OGF_S_LODS);
#ifndef _string_lod
        	CEditableObject* lod_src = Lib.CreateEditObject( m_Source->GetLODs() );
            if (0==lod_src)
            {
            	Log		("! Invalid LOD name:",m_Source->GetLODs());
            	bRes	= false;
            }else
            {
                CExportSkeleton	    E(lod_src);
#else

                F.w_string          ( m_Source->GetLODs() );
#endif

#ifndef _string_lod
                if (!E.ExportAsSimple(F))
                {
                    Log		("! Invalid LOD object:",m_Source->GetLODs());
                    bRes	= false;
                }

            	Lib.RemoveEditObject(lod_src);
            }
#endif
        F.close_chunk	();
    }

    UI->ProgressEnd(pb);

    return bRes;
}
//----------------------------------------------------
struct bm_item{
    CKeyQR* 		_keysQR; 
    CKeyQT8* 		_keysQT8; 
    CKeyQT16* 		_keysQT16; 
    Fvector* 		_keysT;
    void create(u32 len)
    {
        _keysQR 	= xr_alloc<CKeyQR>(len); 
        _keysQT8 	= xr_alloc<CKeyQT8>(len); 
        _keysQT16 	= xr_alloc<CKeyQT16>(len); 
        _keysT 		= xr_alloc<Fvector>(len);
    }
    void destroy()
    {
        xr_free		(_keysQR);
        xr_free		(_keysQT8);
        xr_free		(_keysQT16);
        xr_free		(_keysT);
    }
};

bool CExportSkeleton::ExportMotionKeys(IWriter& F)
{
    if (!!m_Source->m_SMotionRefs.size()||(m_Source->SMotionCount()<1)){
    	Msg("!..Object doesn't have own motion");
     	return !!m_Source->m_SMotionRefs.size();
    }

	SPBItem* pb = UI->ProgressStart(1+m_Source->SMotionCount(),"..Export skeleton motions keys");
    pb->Inc		();

    // mem active motion
    CSMotion* active_motion=m_Source->ResetSAnimation();

    // Motions
    F.open_chunk			(OGF_S_MOTIONS);
    F.open_chunk			(0);
    F.w_u32					(m_Source->SMotionCount());
    F.close_chunk			();
    int smot 				= 1;

    // use global transform
    Fmatrix	mGT,mTranslate,mRotate;
    mRotate.setHPB			(m_Source->a_vRotate.y, m_Source->a_vRotate.x, m_Source->a_vRotate.z);
    mTranslate.translate	(m_Source->a_vPosition);
    mGT.mul					(mTranslate,mRotate);

    for (SMotionIt motion_it=m_Source->FirstSMotion(); motion_it!=m_Source->LastSMotion(); motion_it++, smot++){
        CSMotion* motion 	= *motion_it;

//		if (motion->m_Flags.is(esmStopAtEnd)) Msg("%s - %d",motion->Name(),motion->m_Flags.is(esmStopAtEnd));
        
        F.open_chunk		(smot);
        F.w_stringZ			(motion->Name());
        F.w_u32				(motion->Length());

        u32 dwLen			= motion->Length();
        BoneVec& b_lst 		= m_Source->Bones();

        bm_item* items	 	= xr_alloc<bm_item>(b_lst.size());
        for (u32 itm_idx=0; itm_idx<b_lst.size(); itm_idx++) 
        	items[itm_idx].create(dwLen);
        
        for (int frm=motion->FrameStart(); frm<motion->FrameEnd(); frm++){
            float t 		= (float)frm/motion->FPS();
	        int bone_id 	= 0;
            for(BoneIt b_it=b_lst.begin(); b_it!=b_lst.end(); b_it++, bone_id++){
	            Fvector 	T,R;
                motion->_Evaluate	(bone_id,t,T,R);
                (*b_it)->_Update	(T,R);
            }
            m_Source->CalculateAnimation(motion);
	        bone_id 		= 0;
            for(b_it=b_lst.begin(); b_it!=b_lst.end(); b_it++, bone_id++){
                CBone* B 	= *b_it;
                Fmatrix mat	= B->_MTransform();
//.	            VERIFY		(!motion->GetMotionFlags(bone_id).is(st_BoneMotion::flWorldOrient));
	         	if (B->IsRoot()) mat.mulA_43(mGT);
				Fquaternion	q;
                q.set		(mat);
                CKeyQR&	Kr 	= items[bone_id]._keysQR[frm-motion->FrameStart()];
                Fvector&Kt 	= items[bone_id]._keysT [frm-motion->FrameStart()];
                // Quantize quaternion
                int	_x 		= int(q.x*KEY_Quant); clamp(_x,-32767,32767); Kr.x =  (s16)_x;
                int	_y 		= int(q.y*KEY_Quant); clamp(_y,-32767,32767); Kr.y =  (s16)_y;
                int	_z 		= int(q.z*KEY_Quant); clamp(_z,-32767,32767); Kr.z =  (s16)_z;
                int	_w 		= int(q.w*KEY_Quant); clamp(_w,-32767,32767); Kr.w =  (s16)_w;
                Kt.set		(mat.c);//B->_Offset());
            }
        }
        // free temp storage
        for (itm_idx=0; itm_idx<b_lst.size(); itm_idx++){
        	bm_item& BM 	= items[itm_idx];
            // check T
            R_ASSERT		(dwLen);
            Fvector 		Mt={0,0,0};
            Fvector 		Ct={0,0,0};
            Fvector 		St={0,0,0};
            BOOL			t_present = FALSE;
            BOOL			r_present = FALSE;
            Fvector At		= BM._keysT[0];
            Fvector Bt		= BM._keysT[0];
            for (u32 t_idx=0; t_idx<dwLen; t_idx++){
            	Fvector& t	= BM._keysT[t_idx];
            	Mt.add		(t);
                At.x		= _min(At.x,t.x);
                At.y		= _min(At.y,t.y);
                At.z		= _min(At.z,t.z);
                Bt.x		= _max(Bt.x,t.x);
                Bt.y		= _max(Bt.y,t.y);
                Bt.z		= _max(Bt.z,t.z);
            }
            Mt.div			(dwLen);
            Ct.add			(Bt,At);
            Ct.mul			(0.5f);
            St.sub			(Bt,At);
            St.mul			(0.5f);
            CKeyQR& R		= BM._keysQR[0];
			bool bTransform16Bit = false;
            if(g_force16BitTransformQuant || St.magnitude()>1.5f)
            {
            	bTransform16Bit = true;
                Msg("animation [%s] is 16bit-transform (%f)m", motion->Name(), St.magnitude());
            }
            for (t_idx=0; t_idx<dwLen; t_idx++){
            	Fvector& t	= BM._keysT[t_idx];
            	CKeyQR& r	= BM._keysQR[t_idx];
                if (!Mt.similar(t,EPS_L))							t_present = TRUE;
                if ((R.x!=r.x)||(R.y!=r.y)||(R.z!=r.z)||(R.w!=r.w))	r_present = TRUE;
                
                if(bTransform16Bit)
                {
					CKeyQT16&	Kt 	= BM._keysQT16[t_idx];
					int	_x 		= int(32767.f*(t.x-Ct.x)/St.x); clamp(_x,-32767,32767); Kt.x1 =  (s16)_x;
					int	_y 		= int(32767.f*(t.y-Ct.y)/St.y); clamp(_y,-32767,32767); Kt.y1 =  (s16)_y;
					int	_z 		= int(32767.f*(t.z-Ct.z)/St.z); clamp(_z,-32767,32767); Kt.z1 =  (s16)_z;
				} else {
					CKeyQT8&	Kt 	= BM._keysQT8[t_idx];
					int	_x 		= int(127.f*(t.x-Ct.x)/St.x); clamp(_x,-128,127); Kt.x1 =  (s16)_x;
					int	_y 		= int(127.f*(t.y-Ct.y)/St.y); clamp(_y,-128,127); Kt.y1 =  (s16)_y;
					int	_z 		= int(127.f*(t.z-Ct.z)/St.z); clamp(_z,-128,127); Kt.z1 =  (s16)_z;

				}
            }
            if(bTransform16Bit)
            	St.div	(32767.f);
            else
            	St.div	(127.f);
            // save
            F.w_u8	(u8((t_present?flTKeyPresent:0)|(r_present?0:flRKeyAbsent)|(bTransform16Bit?flTKey16IsBit:0)));
            if (r_present){	
                F.w_u32	(crc32(BM._keysQR,dwLen*sizeof(CKeyQR)));
                F.w		(BM._keysQR,dwLen*sizeof(CKeyQR));
            }else{
                F.w		(&BM._keysQR[0],sizeof(BM._keysQR[0]));
            }
            if (t_present){	
	            if(bTransform16Bit)
                {
                    F.w_u32(crc32(BM._keysQT16,u32(dwLen*sizeof(CKeyQT16))));
                    F.w	(BM._keysQT16,dwLen*sizeof(CKeyQT16));
                }else
                {
                    F.w_u32(crc32(BM._keysQT8,u32(dwLen*sizeof(CKeyQT8))));
                    F.w	(BM._keysQT8,dwLen*sizeof(CKeyQT8));
                }
//	            F.w_u32(crc32(BM._keysQT,u32(dwLen*sizeof(CKeyQT))));
//            	F.w	(BM._keysQT,dwLen*sizeof(CKeyQT));
	            F.w_fvector3(St);
    	        F.w_fvector3(Ct);
            }else{
                F.w_fvector3(Mt);
            }
			BM.destroy();
        }
        xr_free(items);

        F.close_chunk();
    	pb->Inc		();
    }
    F.close_chunk();
	UI->ProgressEnd(pb);

    // restore active motion
    m_Source->SetActiveSMotion(active_motion);
    return true;
}

bool CExportSkeleton::ExportMotionDefs(IWriter& F)
{
    if (!m_Source->IsAnimated()){ 
    	ELog.Msg(mtError,"Object doesn't have any motion or motion refs.");
    	return false;
    }

    bool bRes=true;

	SPBItem* pb = UI->ProgressStart(3,"..Export skeleton motions defs");
    pb->Inc		();

    if (m_Source->m_SMotionRefs.size()){
	    F.open_chunk	(OGF_S_MOTION_REFS);
    	F.w_stringZ		(m_Source->m_SMotionRefs);
	    F.close_chunk	();
	    pb->Inc		();
    }else{
        // save smparams
        F.open_chunk	(OGF_S_SMPARAMS);
        F.w_u16			(xrOGF_SMParamsVersion);
        // bone parts
        BPVec& bp_lst 	= m_Source->BoneParts();
        if (bp_lst.size()){
            if (m_Source->VerifyBoneParts()){
                F.w_u16((u16)bp_lst.size());
                for (BPIt bp_it=bp_lst.begin(); bp_it!=bp_lst.end(); bp_it++){
                    F.w_stringZ	(LowerCase(bp_it->alias.c_str()).c_str());
                    F.w_u16		((u16)bp_it->bones.size());
                    for (int i=0; i<int(bp_it->bones.size()); i++){
                        F.w_stringZ	(bp_it->bones[i].c_str());
                        int idx 	= m_Source->FindBoneByNameIdx(bp_it->bones[i].c_str()); VERIFY(idx>=0);
                        F.w_u32		(idx);
                    }
                }
            }else{
                ELog.Msg(mtError,"Invalid bone parts (missing or duplicate bones).");
                bRes 	= false;
            }
        }else{
            F.w_u16(1);
            F.w_stringZ("default");
            F.w_u16((u16)m_Source->BoneCount());
            for (int i=0; i<m_Source->BoneCount(); i++) F.w_u32(i);
        }
	    pb->Inc		();
        // motion defs
        SMotionVec& sm_lst	= m_Source->SMotions();
        F.w_u16((u16)sm_lst.size());
        for (SMotionIt motion_it=m_Source->FirstSMotion(); motion_it!=m_Source->LastSMotion(); motion_it++){
            CSMotion* motion = *motion_it;
            // verify
            if (!motion->m_Flags.is(esmFX)){
                if (!((motion->m_BoneOrPart==BI_NONE)||(motion->m_BoneOrPart<(int)bp_lst.size()))){
                    ELog.Msg(mtError,"Invalid Bone Part of motion: '%s'.",motion->Name());
                    bRes=false;
                    continue;
                }
            }
            if (bRes){
                // export
                F.w_stringZ	(motion->Name());
                F.w_u32		(motion->m_Flags.get());
                F.w_u16		(motion->m_BoneOrPart);
                F.w_u16		(u16(motion_it-sm_lst.begin()));
                F.w_float	(motion->fSpeed);
                F.w_float	(motion->fPower);
                F.w_float	(motion->fAccrue);
                F.w_float	(motion->fFalloff);

    			u32 sz		= motion->marks.size();
				F.w_u32		(sz);
                for(u32 i=0; i<sz; ++i)
                {
                	motion->marks[i].Save(&F);
                }
            }
        }
	    pb->Inc		();
        F.close_chunk();
    }
    
	UI->ProgressEnd(pb);
    return bRes;
}

bool CExportSkeleton::ExportMotions(IWriter& F)
{
	if (!ExportMotionKeys(F)) 	return false;
	if (!ExportMotionDefs(F)) 	return false;
    return true;
}
//----------------------------------------------------

bool CExportSkeleton::Export(IWriter& F, u8 infl)
{
    if (!ExportGeometry(F,infl)) 					return false;
    if (m_Source->IsAnimated()&&!ExportMotions(F))	return false;
    return true;
};
//----------------------------------------------------



