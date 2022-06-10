#include "stdafx.h"
#pragma hdrstop

#include "ESceneShapeTools.h"
#include "ESceneShapeControls.h"
#include "UI_LevelTools.h"
#include "FrameShape.h"
#include "EShape.h"

void ESceneShapeTools::CreateControls()
{
	inherited::CreateDefaultControls(estDefault);
    AddControl		(xr_new<TUI_ControlShapeAdd>(estDefault,etaAdd,	this));
	// frame
    pFrame 			= xr_new<TfraShape>((TComponent*)0);
	((TfraShape*)pFrame)->tool = this;
}
//----------------------------------------------------
 
void ESceneShapeTools::RemoveControls()
{
	inherited::RemoveControls();
}
//----------------------------------------------------

CCustomObject* ESceneShapeTools::CreateObject(LPVOID data, LPCSTR name)
{
	CCustomObject* O	= xr_new<CEditShape>(data,name);
    O->ParentTools		= this;
    return O;
}
//----------------------------------------------------
#include "scene.h"
void ESceneShapeTools::OnEditLevelBounds(bool recalc)
{
    ObjectList::iterator it = m_Objects.begin();
    ObjectList::iterator it_e = m_Objects.end();


    CEditShape* level_shape = NULL;
    
    for(; it!=it_e; ++it)
    {
    	CEditShape* es = dynamic_cast<CEditShape*>(*it);
        R_ASSERT(es);
        if(es->m_shape_type==eShapeLevelBound)
        {
         	level_shape = es;
        	break;
        }
    }
    bool b_recalc = recalc || (level_shape==NULL);
    
	if(!level_shape)    
    {
		level_shape 			= dynamic_cast<CEditShape*>(CreateObject(NULL, "level_bbox"));
        level_shape->m_shape_type=eShapeLevelBound;
    	Fmatrix 				M;	
        M.identity				();
    	level_shape->add_box	(M);

   		Scene->AppendObject		(level_shape);
    }

    if(b_recalc)
    {
        Fbox 	bg,br;
        Scene->GetBox(br,OBJCLASS_SCENEOBJECT);
        bool r1 = Scene->GetBox(bg,OBJCLASS_GROUP);
        if (r1)
			br.merge(bg);

        Fvector vec;
        br.getsize(vec);
        level_shape->PScale = vec;
//      level_shape->OnUpdateTransform();
//      level_shape->ApplyScale();
        
        br.getcenter(vec);
        level_shape->FPosition = vec;
		
    }
}
void ESceneShapeTools::OnActivate()
{
	inherited::OnActivate();
	((TfraShape*)pFrame)->ebEditLevelBoundMode->Down = false;
}

void ESceneShapeTools::OnDeactivate()
{
	inherited::OnDeactivate();
	((TfraShape*)pFrame)->ebEditLevelBoundMode->Down = false;
}
