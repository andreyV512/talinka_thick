// ---------------------------------------------------------------------------

#ifndef WorkModeH
#define WorkModeH
// ---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "Series.hpp"
#include <ComCtrls.hpp>
#include <windows.h>
#include "IniFiles.hpp"
#include <ImgList.hpp>
#include "Solenoid.h"
#include "DataAquirer.h"

// ! @brief �����, �������������� ����������� ����� ���������������� �����
// ! @brief ���� ������ ����� ������ � �������� ��� ���������.
// ! �� ����, ����������� � ���� ��� ������� ���������.
class WorkThreadClass : public TThread
{

private:
	// ! ������ ������
	void __fastcall Execute();

	// ! ����� ��� ������� � ���������� � ������ 1
	String stext1;
	// ! ����� ��� ������� � ���������� � ������ 2
	String stext2;

	// ! ��������� �������  false - ������, true - ��� ����
	bool TestSolenoid();

	// ! ��������� � �������
	bool Solenoid_ok;
	RawStrobes* rawStrobes;

	// ! ��������� ���������� ������� �����, ������������ �������
	void __fastcall UpdateMainForm();
	void __fastcall ClearCharts();
	void pr(AnsiString _msg);
	__fastcall void AddTickStrobe(unsigned int _tick);
	bool result;
	Solenoid* ThickSolenoid;
	TIniFile *ini;
	void WorkMode(void);
	inline int getvolt(void){return(ThickSolenoid->getchVoltage());};
	ADCBoards* adcboards;
public:
	__fastcall WorkThreadClass(RawStrobes* _rawStrobes,TIniFile* _ini, ADCBoards* _adcBoards);
	__fastcall ~WorkThreadClass();
};

// ---------------------------------------------------------------------------
#endif
