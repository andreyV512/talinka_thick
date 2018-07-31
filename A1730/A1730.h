// ---------------------------------------------------------------------------
#ifndef A1730H
#define A1730H
#include<Classes.hpp>
#include<SyncObjs.hpp>
#include "Signal.h"
#include "uCRListT.h"
#include "Latch.h"
#include<IniFiles.hpp>
#pragma warn -8060
//#include "c:/Advantech/DAQNavi/Inc/bdaqctrl.h"
#include "Inc/bdaqctrl.h"
#pragma warn .8060

using namespace Automation::BDaq;
// ---------------------------------------------------------------------------
class A1730 : private TThread
{
public:
	typedef void __fastcall(__closure*OnEventDef)(void);
	typedef void __fastcall(__closure*OnFrontDef)(unsigned int _tick);
private:
	InstantDiCtrl* instantDiCtrl;
	InstantDoCtrl* instantDoCtrl;

	int period;
	TCriticalSection* cs;
	long startPort;
	long portCount;
	CRListT <CSignal> M;
	CRListT <Latch> L;

	void __fastcall Execute();
	DWORD Read(void);
	DWORD ReadOut(void);
	void Write(DWORD _v);
	bool GetIn(int _index);
	bool GetOut(int _index);
	void Set(int _index,bool _value);
	void WriteSignals(void);
	void ReadSignals(void);
	CSignal* Find(AnsiString _name);
	AnsiString Wait(bool _value,CSignal* _signal,DWORD _tm);
	void Alarm(void);
	bool alarmCycleOn;
	OnFrontDef OnFront;

	void SendFront(unsigned int _tick);
	void Latchterminate0(AnsiString _reason);
	bool IsAlarm;
	void Drop(void);
	void pr(AnsiString _msg);
	bool latchError;
public:
	A1730(int _DevNum,AnsiString _file_name,TIniFile* _ini);
	__fastcall ~A1730(void);
	void SetPeriod(int _period);
	void ClearLatchError(void);
	void SetLatchError(void);

	CSignal* iPCHA; // �� �
	CSignal* iCC; // ���� ����������
	CSignal* iPCHRUN; // �� RUN
	CSignal* iSTROBE; // ����� ����
	CSignal* iCYCLE; // ����
	CSignal* iREADY; // ����������
	CSignal* iCONTROL; // ��������
	CSignal* iCONTROL_END; // ��������

	CSignal* oPCHPOW; // ������� ��
	CSignal* oSCANPOW; // ������� ��
	CSignal* oSOLPOW; // ������� ��������
	CSignal* oWORK; // ������
	CSignal* oMEAS; // ���������
	CSignal* oSHIFT; // ����������
	CSignal* oSTROBE; // �����
	CSignal* oRESULT; // ���������

	CSignal *oSTF;       //  ����� �����������
	CSignal *oRL;        //  ��� �������� 0
	CSignal *oRM;        //  ��� �������� 1
	CSignal *oRH;        //  ��� �������� 2

	double speedTube;
	unsigned controlBegin, controlEnd, currentControl;
	int baseWidth;

	inline int SignalCount(void)
	{
		return (M.Count());
	}

	inline CSignal* GetSignal(int _index)
	{
		return (M[_index]);
	}
	void AlarmCycleOn(bool _v);
	void SetOnFront(OnFrontDef _OnFront);
	void Latchterminate(AnsiString _msg);
	void SetAlarm(bool _IsAlarm);
	void Clear();
};
extern A1730* a1730;
#endif
