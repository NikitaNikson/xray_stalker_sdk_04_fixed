//---------------------------------------------------------------------------
#include "stdafx.h"
#pragma hdrstop

#include "LevelPreferences.h"
#include "ESceneCustomMTools.h"
#include "scene.h"
#include "UI_LevelMain.h"
#include "UI_LevelTools.h"
//---------------------------------------------------------------------------

void CLevelPreferences::Load(CInifile* I)
{
	inherited::Load		(I);                         
    SceneToolsMapPairIt _I 	= Scene->FirstTools();
    SceneToolsMapPairIt _E 	= Scene->LastTools();
    for (; _I!=_E; _I++)
        if (_I->second&&(_I->first!=OBJCLASS_DUMMY))	
        	_I->second->m_EditFlags.flags = R_U32_SAFE("targets",_I->second->ClassName(),_I->second->m_EditFlags.flags);
}

void CLevelPreferences::Save(CInifile* I)
{
	inherited::Save		(I);
    SceneToolsMapPairIt _I 	= Scene->FirstTools();
    SceneToolsMapPairIt _E 	= Scene->LastTools();
    for (; _I!=_E; _I++)
        if (_I->second&&(_I->first!=OBJCLASS_DUMMY))	I->w_u32	("targets",_I->second->ClassName(),_I->second->m_EditFlags.get());
}

void CLevelPreferences::OnEnabledChange(PropValue* prop)
{
	ESceneCustomMTools* M	= Scene->GetMTools(prop->tag); VERIFY(M);
	ExecCommand				(COMMAND_ENABLE_TARGET,prop->tag,M->IsEnabled());
}	

void CLevelPreferences::OnReadonlyChange(PropValue* prop)
{
	ESceneCustomMTools* M	= Scene->GetMTools(prop->tag); VERIFY(M);
	ExecCommand				(COMMAND_READONLY_TARGET,prop->tag,M->IsForceReadonly());
}	

void CLevelPreferences::FillProp(PropItemVec& items)
{
	inherited::FillProp	(items);
    SceneToolsMapPairIt _I 	= Scene->FirstTools();
    SceneToolsMapPairIt _E 	= Scene->LastTools();
    for (; _I!=_E; _I++)
        if (_I->second&&(_I->first!=OBJCLASS_DUMMY)){ 
        	if (_I->second->AllowEnabling()){
                PropValue* V 	= PHelper().CreateFlag32(items,PrepareKey("Scene\\Targets\\Enable",_I->second->ClassDesc()),	&_I->second->m_EditFlags, ESceneCustomMTools::flEnable);
                V->tag			= _I->second->ClassID;
                V->OnChangeEvent.bind(this,&CLevelPreferences::OnEnabledChange);
            }
		    PropValue* V		= PHelper().CreateFlag32(items,PrepareKey("Scene\\Targets\\Read Only",_I->second->ClassDesc()),	&_I->second->m_EditFlags, ESceneCustomMTools::flForceReadonly);
            V->tag				= _I->second->ClassID;
            V->OnChangeEvent.bind(this,&CLevelPreferences::OnReadonlyChange);
        }
}

