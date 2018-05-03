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
#include "Solenoid.h"
//---------------------------------------------------------------------------
class TManageForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *gbThickness;
	TStatusBar *StatusBarBottom;
	TBitBtn *bRotation;
	TTimer *InputTimer;
	TCheckBox *bPowerSU;
	TPanel *pSolenoid;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *eAmperage;
	TEdit *eVoltage;
	TEdit *eTemperature;
	TEdit *eFriquencyRot;
	TLabel *Label4;
	void __fastcall InputTimerTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall bRotationClick(TObject *Sender);
	void __fastcall bPowerSUClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private:	// User declarations

//	AllSignals *sig;					// ��������� �� ���������� ����� ��������� ����
	void ShowCentralizerOpened	( TBitBtn *btn, TPanel *pan );	// ����������� ������������ ���������� (������)
	void ShowCentralizerClosed	( TBitBtn *btn, TPanel *pan );	// ����������� ���������� ���������� (������)
	void ShowModuleinWork		( TBitBtn *btn, TPanel *pan );	// ����������� ������ � ������ �� (������� ���������)
	void ShowModuleinService	( TBitBtn *btn, TPanel *pan );	// ����������� ������ � ������ �� (��������� ������������)
	void ShowModuleMoving		( TBitBtn *btn, TPanel *pan );	// ����������� ������ � ��������
	void ShowModuleState		( byte state, TBitBtn *btn, TPanel *pan );	// ����������� ��������� ������
	bool is_pix_ok;						// ��������� �� �������� ��� ������
	bool butt_enabled;					// ���������� ������ ��� �������� �����
	TColor on, off, move; 		   	    // ����� ��� , ���� ������� � �������� ������
	String centr_on, centr_off;			// ������� ��� � ���� �����������
	String centr_close, centr_open;		// ������� ������ ��� � ���� �����������
	String mod_on, mod_off, mod_mov;	// ������� ������ � ������, � �� � � ��������
	String mod_work, mod_service, mod_dsbl;			// ������� ������ �������� � ��������� �������
	Graphics::TBitmap *centr_cl, *centr_op;			// ������� ��� ������ �����������
	Graphics::TBitmap *mod_serv, *mod_wrk,*mod_mvg;	// ������� ��� ������ ���� ��������� �������
	TIniFile* ini;
	Solenoid* ThickSolenoid;

public:		// User declarations

	__fastcall TManageForm(TComponent* Owner,TIniFile* _ini);

};
//---------------------------------------------------------------------------
extern PACKAGE TManageForm *ManageForm;
//---------------------------------------------------------------------------
#endif
