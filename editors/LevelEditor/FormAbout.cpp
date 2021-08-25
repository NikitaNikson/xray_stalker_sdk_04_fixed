//---------------------------------------------------------------------------
#include "stdafx.h"
#pragma hdrstop

#include "FormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutForm *AboutForm;

//XRCORE_API u32 build_id;
//XRCORE_API LPCSTR build_date;
//---------------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutForm::btnOkClick(TObject *Sender)
{
	AboutForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TAboutForm::FormShow(TObject *Sender)
{
	//lbBuildID->Caption = AnsiString("X-Ray SDK 0.4 SMG Build ") + build_id + ", " + build_date;
	lbBuildID->Caption = AnsiString("X-Ray SDK 0.4 SMG Build 25.08.2021");
}
//---------------------------------------------------------------------------

void __fastcall TAboutForm::lbURLClick1(TObject *Sender)
{
	ShellExecute(Handle, "open", lbURLForumTheme->Caption.c_str(), "", "", SW_SHOWNORMAL);
	lbURLForumTheme->Font->Color = clHotLight;
}
void __fastcall TAboutForm::lbURLClick2(TObject *Sender)
{
	ShellExecute(Handle, "open", lbURLSdkHelp->Caption.c_str(), "", "", SW_SHOWNORMAL);
	lbURLSdkHelp->Font->Color = clHotLight;
}
void __fastcall TAboutForm::lbURLClick3(TObject *Sender)
{
	ShellExecute(Handle, "open", lbURLSdkVideoHelp->Caption.c_str(), "", "", SW_SHOWNORMAL);
	lbURLSdkVideoHelp->Font->Color = clHotLight;
}
//---------------------------------------------------------------------------
