//---------------------------------------------------------------------------

#ifndef ManageH
#define ManageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "Inverter.h"

#include <ComCtrls.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
class TManageForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *gbThickness;
	TStatusBar *StatusBarBottom;
	TBitBtn *bRotation;
	TCheckBox *cbRL;
	TCheckBox *cbRM;
	TCheckBox *cbRH;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall bRotationClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private:	// User declarations

//	AllSignals *sig;					// компонент по управлению всеми сигналами плат
	void ShowCentralizerOpened	( TBitBtn *btn, TPanel *pan );	// отображение разомкнутого центратора (схвата)
	void ShowCentralizerClosed	( TBitBtn *btn, TPanel *pan );	// отображение замкнутого центратора (схвата)
	void ShowModuleinWork		( TBitBtn *btn, TPanel *pan );	// отображение модуля в режиме РП (рабочее положение)
	void ShowModuleinService	( TBitBtn *btn, TPanel *pan );	// отображение модуля в режиме ПО (положение обслуживания)
	void ShowModuleMoving		( TBitBtn *btn, TPanel *pan );	// отображение модуля в движении
	void ShowModuleState		( byte state, TBitBtn *btn, TPanel *pan );	// отображение состояния модуля
	bool is_pix_ok;						// загружены ли картинки для кнопок
	bool butt_enabled;					// блокировка кнопок при движении трубы
	TColor on, off, move; 		   	    // цвета вкл , выкл сигнала и движения модуля
	String centr_on, centr_off;			// надписи вкл и выкл центраторов
	String centr_close, centr_open;		// надписи кнопок вкл и выкл центраторов
	String mod_on, mod_off, mod_mov;	// надписи модуль в работе, в по и в движении
	String mod_work, mod_service, mod_dsbl;			// надписи кнопок поднятия и опускания модулей
	Graphics::TBitmap *centr_cl, *centr_op;			// рисунки для кнопок центраторов
	Graphics::TBitmap *mod_serv, *mod_wrk,*mod_mvg;	// рисунки для кнопок мены состояния модулей
	TIniFile* ini;
   //	Solenoid* ThickSolenoid;

public:		// User declarations

	__fastcall TManageForm(TComponent* Owner,TIniFile* _ini);

};
//---------------------------------------------------------------------------
extern PACKAGE TManageForm *ManageForm;
//---------------------------------------------------------------------------
#endif
