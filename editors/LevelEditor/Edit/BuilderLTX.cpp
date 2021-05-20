//----------------------------------------------------
// file: BuilderLTX.cpp
//----------------------------------------------------

#include "stdafx.h"
#pragma hdrstop

#include "Builder.h"
#include "Scene.h"
#include "../ECore/Editor/EditObject.h"
#include "SceneObject.h"
#include "ELight.h"
#include "SpawnPoint.h"
#include "WayPoint.h"
#include "xr_ini.h"
#include "xr_efflensflare.h"
#include "GroupObject.h"
#include "sector.h"
//----------------------------------------------------

//----------------------------------------------------
BOOL SceneBuilder::ParseLTX(CInifile* pIni, ObjectList& lst, LPCSTR prefix)
{
    return TRUE;
}
//----------------------------------------------------

BOOL SceneBuilder::BuildLTX()
{
	bool bResult	= true;
	int objcount 	= Scene->ObjCount();
	if( objcount <= 0 ) return true;

	xr_string ltx_filename	= MakeLevelPath("level.ltx");

    if (FS.exist(ltx_filename.c_str()))
    	EFS.MarkFile(ltx_filename.c_str(),true);

	// -- defaults --           
    IWriter* F		= FS.w_open(ltx_filename.c_str());
    if (F){
		string256	buff;
    	F->w_string("[map_usage]");
        if(Scene->m_LevelOp.m_bDeathmatch)
        	F->w_string("deathmatch");
        if(Scene->m_LevelOp.m_bTeamDeathmatch)
        	F->w_string("teamdeathmatch");
        if(Scene->m_LevelOp.m_bArtefacthunt)
        	F->w_string("artefacthunt");

        F->w_string( ";");
        F->w_string( "; level script file");
        if(Scene->m_LevelOp.m_BOPText.size())
            F->w_stringZ( Scene->m_LevelOp.m_BOPText );
		
		ObjectIt _F = Scene->FirstObj(OBJCLASS_SECTOR);
		ObjectIt _E = Scene->LastObj(OBJCLASS_SECTOR);

		F->w_string(";");
		F->w_string("[sub_level_map]");
		for(;_F!=_E;++_F)
		{
			CSector* _S		= (CSector*)(*_F);
			sprintf			(buff,"%d = %d", _S->m_sector_num, _S->m_map_idx);
			F->w_string		(buff);
		}

        FS.w_close	(F);
    }else{
    	bResult 	= false;
    }

	return bResult;
}

