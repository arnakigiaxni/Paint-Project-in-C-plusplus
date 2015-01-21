//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"   //dilosi protis formas
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

//an o xristis patisi "nai" kata tin emfanisi tis formas tote tha klisoun
//kai oi dio formes kai i efarmogi tha termatisti
void __fastcall TForm2::YesButtonClick(TObject *Sender)
{
  Form1->Close();
  Form2->Close();
}
//---------------------------------------------------------------------------

//an o xristis patisi "oxi" tote tha klisi i deuteri forma kai tha sinexisi
//kanonika stin proti forma
void __fastcall TForm2::NoButtonClick(TObject *Sender)
{
   Form2->Close();
}
//---------------------------------------------------------------------------

