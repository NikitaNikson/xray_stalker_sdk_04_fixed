#include "stdafx.h"
#pragma hdrstop

#include "ESceneObjectControls.h"
#include "UI_LevelTools.h"
#include "../ECore/Editor/Library.h"
#include "scene.h"
#include "SceneObject.h"
#include "ESceneObjectTools.h"
#include "FrameObject.h"
#include "LeftBar.h"
#include "UI_LevelMain.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
__fastcall TUI_ControlObjectAdd::TUI_ControlObjectAdd(int st, int act, ESceneCustomMTools* parent):TUI_CustomControl(st,act,parent)
{
}

bool __fastcall TUI_ControlObjectAdd::Start(TShiftState Shift)
{
    if (Shift==ssRBOnly){ ExecCommand(COMMAND_SHOWCONTEXTMENU,OBJCLASS_SCENEOBJECT); return false;}
    TfraObject* fraObject = (TfraObject*)parent_tool->pFrame; VERIFY(fraObject);
	Fvector p,n;
	if(!LUI->PickGround(p,UI->m_CurrentRStart,UI->m_CurrentRNorm,1,&n)) return false;
    { // pick already executed (see top)
		ESceneObjectTools* ot = dynamic_cast<ESceneObjectTools*>(parent_tool);
    	LPCSTR N;
        if (ot->IsAppendRandomActive()&&ot->m_AppendRandomObjects.size()){
        	N = ot->m_AppendRandomObjects[Random.randI(ot->m_AppendRandomObjects.size())].c_str();  
        }else{
            N = ((TfraObject*)parent_tool->pFrame)->Current();
            if(!N){
                ELog.DlgMsg(mtInformation,"Nothing selected.");
                return false;
            }
        }

        string256 namebuffer;
        Scene->GenObjectName(OBJCLASS_SCENEOBJECT, namebuffer, N);
        CSceneObject *obj = xr_new<CSceneObject>((LPVOID)0,namebuffer);
        CEditableObject* ref = obj->SetReference(N);
        if (!ref){
        	ELog.DlgMsg(mtError,"TUI_ControlObjectAdd:: Can't load reference object.");
        	xr_delete(obj);
        	return false;
        }
/*        if (ref->IsDynamic()){
            ELog.DlgMsg(mtError,"TUI_ControlObjectAdd:: Can't assign dynamic object.");
            xr_delete(obj);
            return false;
        }
*/
        if (ot->IsAppendRandomActive()){
            Fvector S;
            if (ot->IsAppendRandomRotationActive()){
            	Fvector p;
                p.set(	Random.randF(ot->m_AppendRandomMinRotation.x,ot->m_AppendRandomMaxRotation.x),
                 		Random.randF(ot->m_AppendRandomMinRotation.y,ot->m_AppendRandomMaxRotation.y),
                        Random.randF(ot->m_AppendRandomMinRotation.z,ot->m_AppendRandomMaxRotation.z));
                obj->PRotation = p;
            }
            if (ot->IsAppendRandomScaleActive()){
            	Fvector s;
                if (ot->IsAppendRandomScaleProportional()){
                    s.x		= Random.randF(ot->m_AppendRandomMinScale.x,ot->m_AppendRandomMaxScale.x);
                    s.set	(s.x,s.x,s.x);
                }else{
                    s.set(	Random.randF(ot->m_AppendRandomMinScale.x,ot->m_AppendRandomMaxScale.x),
                            Random.randF(ot->m_AppendRandomMinScale.y,ot->m_AppendRandomMaxScale.y),
                            Random.randF(ot->m_AppendRandomMinScale.z,ot->m_AppendRandomMaxScale.z));
                }
                obj->PScale = s;
            }
        }
        obj->MoveTo(p,n);

        Scene->SelectObjects(false,OBJCLASS_SCENEOBJECT);
        Scene->AppendObject( obj );
        if (Shift.Contains(ssCtrl)) ExecCommand(COMMAND_SHOW_PROPERTIES);
        if (!Shift.Contains(ssAlt)) ResetActionToSelect();
    }
    return false;
}

void __fastcall TUI_ControlObjectAdd::Move(TShiftState _Shift)
{
}
bool __fastcall TUI_ControlObjectAdd::End(TShiftState _Shift)
{
    return true;
}


