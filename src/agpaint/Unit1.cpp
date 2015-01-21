//---------------------------------------------------------------------------

#include <vcl.h>
#include <jpeg.hpp>
#include <Printers.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"   //dilosi deuteris formas
#include "Unit3.h"   //dilosi tritis formas
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"
#pragma resource "extrares.res"   //dilosi tou arxiou extrares
                                  //to opio periexi tous kersores
TForm1 *Form1;
TPicture *SkinImage;  //dilosi skinimage to opio tha xrisimeusi gia na
                      //valoume eikona sto toolbar
TImage *undo;    //dilosi eikonas undo tin opoia xrisimopoioume gia to undo
TImage *redo;   //dilosi eikonas redo tin opoia xrisimopoioume gia to redo

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{     //doublebuffered sti forma kai sto scrollbox gia na antimetopisoume
      //to flickering pou parousiazete
        DoubleBuffered=true;
        ScrollBox1->DoubleBuffered=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  HINSTANCE HInst;
  {   //kanoume load tous analogous kersores pou tha xrisimopoihsoume
    HInst = reinterpret_cast<HINSTANCE>(HInstance);
    Screen->Cursors[crFill] = LoadCursor(HInst, "FILL");  //kouvas gia to fill
    Screen->Cursors[crPlus] = LoadCursor(HInst, "PLUS");  //stavros gia ta sximata
    Screen->Cursors[crDraw] = LoadCursor(HInst, "DRAW");  //molivi
    Screen->Cursors[crErase] = LoadCursor(HInst, "ERASE"); //goma
    Cursor = TCursor(crDraw);
   }
   {
   SkinImage=new TPicture;   //anoigma tis eikonas ap' to arxeio pou tha
                             //valoume sto toolbar...me onome toolpic.bmp
   SkinImage->LoadFromFile("toolpic.bmp");
   }
        {  //kanoume disabled ta koumpia undo/redo kata to anoigma tis formas
        Undo1->Enabled=false;
        Redo1->Enabled=false;
        ToolUndo->Enabled=false;
        ToolRedo->Enabled=false;
       }
}
//---------------------------------------------------------------------------

//kathorizoume tis default times tn shapes
//FG=Foreground color=mavro
//BG=Background color=aspro
//epilogi FG color me aristero click eno BG color me deksi
void __fastcall TForm1::ColorGrid1Change(TObject *Sender)
{
 FGShape->Brush->Color = ColorGrid1->ForegroundColor;
    if (FGShape->Brush->Color == TColor(clBlack))
        FGShape->Pen->Color = TColor(clWhite);
    else
        FGShape->Pen->Color = TColor(clBlack);

    BGShape->Brush->Color = ColorGrid1->BackgroundColor;
    if (BGShape->Brush->Color == TColor(clBlack))
        BGShape->Pen->Color = TColor(clWhite);
    else
        BGShape->Pen->Color = TColor(clBlack);
}

//--------------------------------------------------------------------------

//simvan kata to opio to gemisma xromatos perni ton analogo kersora (kouva)
void __fastcall TForm1::FillButtonClick(TObject *Sender)
{
     Form1->Cursor=TCursor(crFill);
     ScrollBox1->Cursor=TCursor(crFill);
}
//---------------------------------------------------------------------------

//simvan kata to opio to molivi perni ton analogo kersora (molivi)
void __fastcall TForm1::PencilButtonClick(TObject *Sender)
{
        Form1->Cursor=TCursor(crDraw);
        ScrollBox1->Cursor=TCursor(crDraw);
}
//---------------------------------------------------------------------------

//simvan kata to opio i goma perni ton analogo kersora (goma)
void __fastcall TForm1::EraseButtonClick(TObject *Sender)
{
        Form1->Cursor=TCursor(crErase);
        ScrollBox1->Cursor=TCursor(crErase);
}
//---------------------------------------------------------------------------

//simvan kata to patima tou pontikiou sto image1
void __fastcall TForm1::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        undo = new TImage(this); //dimiourgia neas eikonas sto temp
        undo->Picture = Image1->Picture;
        Undo1->Enabled=true;    //energopoioume to undo
        Redo1->Enabled=false;   //apenergopoioume to redo
        ToolUndo->Enabled=true;
        ToolRedo->Enabled=false;

    if (Form1->FillButton->Down)
    {  //kouvas, xrisimopoiei to FG color an patisoume aristero click
    //kai to BG color an patisoume deksi click
    //zografizi mexri na vrei diaforetiko xroma opote kai stamata
        if (Button == mbLeft)
            Image1->Canvas->Brush->Color = Form1->FGShape->Brush->Color;
        else
            Image1->Canvas->Brush->Color = Form1->BGShape->Brush->Color;
            Image1->Canvas->FloodFill(X, Y, Image1->Canvas->Pixels[X][Y], fsSurface);
        return;
    }
    if (Button != mbLeft)
        return;

//goma i opoia perni to xroma tou BG color kai exei to megethos tou trackbar +10 pixel
    if (Form1->EraseButton->Down)
    {
        Image1->Canvas->Pen->Color = BGShape->Brush->Color;
        Image1->Canvas->Brush->Color = BGShape->Brush->Color;
        Image1->Canvas->Pen->Width = SizeBar->Position+10;
        Image1->Canvas->Rectangle(X-1, Y-1, X, Y);
        Image1->Canvas->MoveTo(X,Y);
        return;

        undo = new TImage(this);
        undo->Picture = Image1->Picture;
        Undo1->Enabled=true;
        Redo1->Enabled=false;
        ToolUndo->Enabled=true;
        ToolRedo->Enabled=false;
    }

//molivi to opoio perni to xroma tou FG color kai exei to megethos tou trackbar
    if (Form1->PencilButton->Down)
    {
        Image1->Canvas->Pen->Color = Form1->FGShape->Brush->Color;
        Image1->Canvas->Brush->Color = Form1->BGShape->Brush->Color;
        Image1->Canvas->Pen->Width = SizeBar->Position;
        Image1->Canvas->MoveTo(X,Y);
        return;

        undo = new TImage(this);
        undo->Picture = Image1->Picture;
        Undo1->Enabled=true;
        Redo1->Enabled=false;
        ToolUndo->Enabled=true;
        ToolRedo->Enabled=false;
    }

    InitialX = X;    //dinoume tin thesi X,Y tou kersora stis metavlites
    InitialY = Y;
    X1=X;
    Y1=Y;

    TmpImage = new TImage(this);
    TmpImage->Picture = Image1->Picture;
}
//---------------------------------------------------------------------------

//simvan to opoio pragmatopoieite kata to sirsimo tou pontikiou eno exi patimeno to click
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
    if (!Shift.Contains(ssLeft))
        return;

    if (Form1->FillButton->Down)
        return;

    if (Form1->PencilButton->Down) //zografizi analogos to antikimeno pou xrisimopoioume
    {
        Image1->Canvas->LineTo(X,Y);  //X,Y oi sintetagmenes tou kersora pano sto image1
        return;
    }

    if (Form1->EraseButton->Down)
    {
        Image1->Canvas->LineTo(X,Y);
        return;
    }
    DrawShape(X, Y);
}
//---------------------------------------------------------------------------

//simvan kata to opio afinoume to click tou pontikiou
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        redo = new TImage(this);
        redo->Picture = Image1->Picture;

    if (Button != mbLeft)
        return;

    if ((Form1->FillButton->Down) || (Form1->PencilButton->Down))
        return;

    if (Form1->EraseButton->Down)
    {
        Image1->Canvas->Pen->Width = 1;
        return;
    }
    DrawShape(X, Y);
    delete TmpImage;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DrawShape(int X, int Y)
{
    Image1->Picture = TmpImage->Picture;

//sta sximata me gemisma, to perivlima ine to FG color eno to gemisma to BG color
    Image1->Canvas->Brush->Color = Form1->BGShape->Brush->Color; //gemisma BG color
    Image1->Canvas->Pen->Color = Form1->FGShape->Brush->Color; //pena FG color
    Image1->Canvas->Pen->Width = SizeBar->Position;  //megethos=thesi tou sizebar


    if (Form1->CircleButton->Down)  //kiklos
        Image1->Canvas->Arc(InitialX, InitialY, X, Y, X, Y, X, Y);
    else if (Form1->SquareButton->Down)   //orthogonio
        {
        Image1->Canvas->Pen->Width = SizeBar->Position;
        Image1->Canvas->Pen->Color = Form1->FGShape->Brush->Color;
        Image1->Canvas->Brush->Style= bsClear; //gia diafanes gemisma
        Image1->Canvas->Rectangle(InitialX, InitialY, X, Y);
        }
    else if (Form1->SolidCirButton->Down)   //kiklos me gemisma
        Image1->Canvas->Ellipse(InitialX, InitialY, X, Y);
    else if (Form1->SolidSqButton->Down)    //orthogonio me gemisma
        Image1->Canvas->Rectangle(InitialX, InitialY, X, Y);
    else if (Form1->RnRectButton->Down) //orthogonio me kampiles
        {
        Image1->Canvas->Brush->Style= bsClear;
        Image1->Canvas->RoundRect(InitialX, InitialY, X, Y, X1, Y1);
        }
    else if (Form1->FillRnRectButton->Down)//orthogonio me kampiles kai gemisma
        {
        Image1->Canvas->RoundRect(InitialX, InitialY, X, Y, X1, Y1);
        }
    else if (Form1->LineButton->Down)  //grammi
        {
        Image1->Canvas->Pen->Width = SizeBar->Position;
        Image1->Canvas->MoveTo(X, Y);
        Image1->Canvas->LineTo(InitialX, InitialY);
        return;
        }
}
//---------------------------------------------------------------------------
//simvan otan patiete to open...
//anoigma bmp & jpg eikonon

void __fastcall TForm1::OpenPicture1Click(TObject *Sender)
{
    OpenPictureDialog1->Filter =
       "Bmp files (*.bmp)|*.BMP| JPEG images (*.jpg) | *.jpg; " ;
    if (OpenPictureDialog1->Execute())
    {
        if (!FileExists(OpenPictureDialog1->FileName))
            return;
        AnsiString temp2 = ExtractFileName(OpenPictureDialog1->FileName);
        AnsiString temp = ExtractFileExt(OpenPictureDialog1->FileName);
        AnsiString Ext = temp.LowerCase();

        if (Ext.AnsiPos("jpg") > 0)
        {
            TJPEGImage *myjpeg = new TJPEGImage();
            myjpeg->LoadFromFile(OpenPictureDialog1->FileName);
            myjpeg->DIBNeeded();
            Image1->Picture->Bitmap->Assign(myjpeg);
            delete myjpeg;
        }
        else if (Ext.AnsiPos("bmp") > 0)
        {
            Image1->Picture->Bitmap->LoadFromFile(OpenPictureDialog1->FileName);
        }
    }
        {
        Undo1->Enabled=false; //apenergopoioume ta undo/redo
        Redo1->Enabled=false;
        ToolUndo->Enabled=false;
        ToolRedo->Enabled=false;
        }
}
//---------------------------------------------------------------------------

//simvan gia to anoigma tis deuteris formas otan patiete to exit
void __fastcall TForm1::Exit1Click(TObject *Sender)
{
        Form2->ShowModal();
}
//---------------------------------------------------------------------------

//simvan gia tin apothikeusi tis eikonas otan patiete to save
//dinatotita gia apothikeusi se bmp & jpg morfi
void __fastcall TForm1::SavePic1Click(TObject *Sender)
{
  SavePictureDialog1->Title = "Save Image";
  SavePictureDialog1->DefaultExt = "jpg";
  SavePictureDialog1->Filter =
       "JPEG images (*.jpg) | *.jpg; | Bmp files (*.bmp)|*.BMP" ;
  SavePictureDialog1->FilterIndex = 1;
    if (SavePictureDialog1->Execute())
    {
        AnsiString temp2 = ExtractFileName(SavePictureDialog1->FileName);
        AnsiString temp = ExtractFileExt(SavePictureDialog1->FileName);
        AnsiString Ext = temp.LowerCase();

        if (Ext.AnsiPos("jpg") > 0)
        {
            TJPEGImage *jp = new TJPEGImage();
            try
            {
              jp->Assign(Image1->Picture->Bitmap);
              jp->SaveToFile(SavePictureDialog1->FileName);
            }
            __finally
            {
              delete jp;
            }
        }
        else  if (Ext.AnsiPos("bmp") > 0)
        {
           Image1->Picture->Bitmap->SaveToFile(SavePictureDialog1->FileName);
        }
    }
}
//---------------------------------------------------------------------------

//anoigma perisoteron xromaton kata to patima tou "more fg colors"
//apo8ikeusi xromatos sto FG shape
void __fastcall TForm1::ColorButtonClick(TObject *Sender)
{
     if(ColorDialog1->Execute())
        {
                Form1->FGShape->Brush->Color=ColorDialog1->Color;
        }
}
//---------------------------------------------------------------------------

//simvan gia to anoigma tis tritis formas otan patiete to exit
void __fastcall TForm1::About1Click(TObject *Sender)
{
  Form3->ShowModal();
}
//---------------------------------------------------------------------------

//anoigma perisoteron xromaton kata to patima tou "more bg colors"
//apo8ikeusi xromatos sto BG shape
void __fastcall TForm1::Color2ButtonClick(TObject *Sender)
{
       if(ColorDialog1->Execute())
        {
                Form1->BGShape->Brush->Color=ColorDialog1->Color;
        }
}
//---------------------------------------------------------------------------

//ektiposi tis formas
void __fastcall TForm1::Print1Click(TObject *Sender)
{
        if(PrinterSetupDialog1->Execute())
        {
        Form1->Print();
        }
}
//---------------------------------------------------------------------------

//simvan gia "neo arxeio"....apenergopoihsi tou undo/redo
void __fastcall TForm1::New1Click(TObject *Sender)
{
        Image1->Picture=0;
        Undo1->Enabled=false;
        Redo1->Enabled=false;
        ToolUndo->Enabled=false;
        ToolRedo->Enabled=false;
}
//---------------------------------------------------------------------------

//edit to opoio mas deixnei tin timi tou sizebar ka8e fora
void __fastcall TForm1::Edit1Change(TObject *Sender)
{
        Form1->Edit1->Text=SizeBar->Position;        
}
//---------------------------------------------------------------------------

//simvan kata to opio ta sximata pernoun ton analogo kersora (stavros)
void __fastcall TForm1::CircleButtonClick(TObject *Sender)
{
    Form1->Cursor = TCursor(crPlus);
    ScrollBox1->Cursor=TCursor(crPlus);
}
//---------------------------------------------------------------------------

//apothikeusi tis eikonas pou anoiksame proigoumenos pano sto toolbar
void __fastcall TForm1::ToolBar1CustomDraw(TToolBar *Sender,
      const TRect &ARect, bool &DefaultDraw)
{
        ToolBar1->Canvas->StretchDraw(ARect, SkinImage->Graphic);
}
//---------------------------------------------------------------------------

//simvan kata to patima tou undo
//apenergopoihsi undo....energopoihsi redo
void __fastcall TForm1::Undo1Click(TObject *Sender)
{
        Image1->Picture= undo->Picture;
        Undo1->Enabled=false;
        Redo1->Enabled=true;
        ToolUndo->Enabled=false;
        ToolRedo->Enabled=true;
}
//---------------------------------------------------------------------------

//simvan kata to patima tou redo
//apenergopoihsi redo...energopoihsi undo
void __fastcall TForm1::Redo1Click(TObject *Sender)
{
        Image1->Picture = redo->Picture;
        Redo1->Enabled=false;
        Undo1->Enabled=true;
        ToolUndo->Enabled=true;
        ToolRedo->Enabled=false;
}
//---------------------------------------------------------------------------

