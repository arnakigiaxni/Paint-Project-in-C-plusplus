//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <cgrid.h>
#include "CGRID.h"
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Graphics.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>

const int crFill  = 5;   //δηλωση των κερσορων
const int crPlus  = 6;
const int crDraw  = 7;
const int crErase = 8;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *FGShape;
        TShape *BGShape;
        TSpeedButton *PencilButton;
        TSpeedButton *FillButton;
        TSpeedButton *EraseButton;
        TSpeedButton *CircleButton;
        TSpeedButton *SquareButton;
        TSpeedButton *SolidCirButton;
        TSpeedButton *SolidSqButton;
        TCColorGrid *ColorGrid1;
        TImage *Image1;
        TSpeedButton *LineButton;
        TMainMenu *MainMenu1;
        TMenuItem *file1;
        TMenuItem *OpenPicture1;
        TMenuItem *SavePic1;
        TMenuItem *Exit1;
        TColorDialog *ColorDialog1;
        TSpeedButton *ColorButton;
        TMenuItem *Help1;
        TMenuItem *About1;
        TSpeedButton *Color2Button;
        TMenuItem *Print1;
        TPrinterSetupDialog *PrinterSetupDialog1;
        TTrackBar *SizeBar;
        TLabel *Label2;
        TMenuItem *New1;
        TToolBar *ToolBar1;
        TToolButton *NewTool;
        TToolButton *OpenTool;
        TToolButton *SaveTool;
        TToolButton *PrintTool;
        TImageList *ImageList1;
        TMenuItem *N1;
        TToolButton *AboutButton;
        TToolButton *ToolButton1;
        TSpeedButton *RnRectButton;
        TEdit *Edit1;
        TSpeedButton *FillRnRectButton;
        TOpenPictureDialog *OpenPictureDialog1;
        TSavePictureDialog *SavePictureDialog1;
        TScrollBox *ScrollBox1;
        TImage *Image2;
        TToolButton *ToolUndo;
        TToolButton *ToolRedo;
        TMenuItem *Edit2;
        TMenuItem *Undo1;
        TMenuItem *Redo1;
        TToolButton *ToolButton2;
        void __fastcall ColorGrid1Change(TObject *Sender);
        void __fastcall FillButtonClick(TObject *Sender);
        void __fastcall PencilButtonClick(TObject *Sender);
        void __fastcall EraseButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall OpenPicture1Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall SavePic1Click(TObject *Sender);
        void __fastcall ColorButtonClick(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall Color2ButtonClick(TObject *Sender);
        void __fastcall Print1Click(TObject *Sender);
        void __fastcall New1Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall CircleButtonClick(TObject *Sender);
        void __fastcall ToolBar1CustomDraw(TToolBar *Sender,
          const TRect &ARect, bool &DefaultDraw);
        void __fastcall Undo1Click(TObject *Sender);
        void __fastcall Redo1Click(TObject *Sender);




private:
    int InitialX;   //δηλωση των μεταβλητων X & Y
    int InitialY;
    int X1;
    int Y1;


 
    
    TImage *TmpImage;	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
       
        void __fastcall DrawShape(int X, int Y);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
