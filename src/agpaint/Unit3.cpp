//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

//an patithei to "ok" tote klini i form 3
void __fastcall TForm3::SpeedButton1Click(TObject *Sender)
{
Form3->Close();
}
//---------------------------------------------------------------------------
