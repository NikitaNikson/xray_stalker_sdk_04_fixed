//---------------------------------------------------------------------------
#include "stdafx.h"
#pragma hdrstop

#include "ESceneWallmarkControls.h"

#include "ESceneWallmarkTools.h"
#include "../ECore/Editor/ui_main.h"
#include "scene.h"
#include "UI_LevelTools.h"
#include "UI_LevelMain.h"

//------------------------------------------------------------------------------
// Node Add
//------------------------------------------------------------------------------
TUI_ControlWallmarkAdd::TUI_ControlWallmarkAdd(int st, int act, ESceneCustomMTools* parent):TUI_CustomControl(st,act,parent){
}

bool __fastcall TUI_ControlWallmarkAdd::Start(TShiftState Shift)
{
    ESceneWallmarkTools* S 	= (ESceneWallmarkTools*)parent_tool;
    
    S->SelectObjects		(false);
    wm_cnt					= 0;
    if (S->AddWallmark(UI->m_CurrentRStart,UI->m_CurrentRNorm)){
    	wm_cnt++;
		if (!Shift.Contains(ssAlt)){ 
		    Scene->UndoSave		();
        	ResetActionToSelect	();
            return false;
        }else return true;
    }
    return false;
}
void TUI_ControlWallmarkAdd::Move(TShiftState _Shift)
{
}
bool TUI_ControlWallmarkAdd::End(TShiftState _Shift)
{
	if (!_Shift.Contains(ssAlt))ResetActionToSelect();
	if (wm_cnt)	    			Scene->UndoSave		();
	return true;
}

//------------------------------------------------------------------------------------
// WM Move
//------------------------------------------------------------------------------------
TUI_ControlWallmarkMove::TUI_ControlWallmarkMove(int st, int act, ESceneCustomMTools* parent):TUI_CustomControl(st,act,parent)
{
}
bool TUI_ControlWallmarkMove::Start(TShiftState Shift)
{
    if (Shift.Contains(ssCtrl)){
	    ESceneWallmarkTools* S 	= (ESceneWallmarkTools*)parent_tool;
    	if (S->MoveSelectedWallmarkTo(UI->m_CurrentRStart,UI->m_CurrentRNorm))
            Scene->UndoSave();
    }
    return false;
}

void __fastcall TUI_ControlWallmarkMove::Move(TShiftState _Shift)
{
}

bool __fastcall TUI_ControlWallmarkMove::End(TShiftState _Shift)
{
	return false;
}

