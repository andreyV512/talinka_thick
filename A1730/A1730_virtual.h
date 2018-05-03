#ifndef A1730_virtualH
#define A1730_virtualH
#include<IniFiles.hpp>
#include "uCRListT.h"
#include "Signal.h"
#include "Latch.h"
class A1730_virtual
{
public:
	typedef void __fastcall(__closure*OnEventDef)(void);
	typedef void __fastcall(__closure*OnFrontDef)(unsigned int _tick);
private:
	A1730_virtual(int _DevNum,AnsiString _file_name,TIniFile* _ini,bool _ReadOnly);
/*
	int period;
*/
	TCriticalSection* cs;
/*
	long startPort;
	long portCount;
*/
	CRListT <CSignal> M;
/*
	CRListT <Latch> L;

	void __fastcall Execute();
	DWORD Read(void);
	DWORD ReadOut(void);
	void Write(DWORD _v);
	bool GetIn(int _index);
	bool GetOut(int _index);
	void Set(int _index,bool _value);
*/
	void WriteSignals(void);
/*
	void ReadSignals(void);
*/
	CSignal* Find(AnsiString _name);
	AnsiString Wait(bool _value,CSignal* _signal,DWORD _tm);
/*
	void Alarm(void);
	bool alarmCycleOn;
	OnFrontDef OnFront;

	void SendFront(unsigned int _tick);
	void Latchterminate0(AnsiString _reason);
	bool IsAlarm;
	void Drop(void);
*/
public:
	static A1730_virtual* Create(int _DevNum,AnsiString _file_name,TIniFile* _ini,
		bool _ReadOnly=false);
	__fastcall ~A1730_virtual(void);
	void SetPeriod(int _period);

	CSignal* iPCHA; // �� �
	CSignal* iCC; // ���� ����������
	CSignal* iPCHRUN; // �� RUN
	CSignal* iSTROBE; // ����� ����
	CSignal* iCYCLE; // ����
	CSignal* iREADY; // ����������
	CSignal* iCONTROL; // ��������

	CSignal* oPCHPOW; // ������� ��
	CSignal* oSCANPOW; // ������� ��
	CSignal* oSOLPOW; // ������� ��������
	CSignal* oWORK; // ������
	CSignal* oMEAS; // ���������
	CSignal* oSHIFT; // ����������
	CSignal* oSTROBE; // �����
	CSignal* oRESULT; // ���������

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
	void pr(AnsiString _msg);
};
#endif
