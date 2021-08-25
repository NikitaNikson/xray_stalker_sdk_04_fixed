//---------------------------------------------------------------------------

#ifndef FormAboutH
#define FormAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "ElCLabel.hpp"
#include "ElURLLabel.hpp"
//---------------------------------------------------------------------------
class TAboutForm : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TLabel *lbBuildID;
	TLabel *LabelCopyright;
	TLabel *LabelForumTheme;
	TLabel *LabelSdkHelp;
	TLabel *LabelSdkVideoHelp;
	TButton *btnOk;
	TLabel *lbURLForumTheme;
	TLabel *lbURLSdkHelp;
	TLabel *lbURLSdkVideoHelp;
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall lbURLClick1(TObject *Sender);
	void __fastcall lbURLClick2(TObject *Sender);
	void __fastcall lbURLClick3(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAboutForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutForm *AboutForm;
//---------------------------------------------------------------------------
#endif
