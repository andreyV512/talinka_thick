//---------------------------------------------------------------------------

#ifndef InverterH
#define InverterH
#include "MitCome/uCInv.h"
#include "vcl.h"
#include <IniFiles.hpp>

//------------------------------------------------------------------------------
class rotationThread;
class Inverter
{
	public:
		Inverter(TIniFile* _ini);
		~Inverter();
		//! @brief ������������� �������� � ���� �� ����������
		//! @param number - ����� ������ � ���������� ( 4,5,6 )
		//! @param value  - �������� � ��
		bool setParameterSpeed(int number, int value);
		//! @param number ����� ������ �� (4,5,6)
		int getParameterSpeed(int number);
		//! �������� ��������
		bool startRotation();
		//! ������������� ��������
		bool stopRotation();
		//! ��������� ��� ��������, ����� ��� �������� � ��������� ������
		bool stateRead();
		//! ��������� �� � ����� NET
		bool NETManage();
		//! ���������� ������ � ����������
		bool ResetErrors();
	private:
		CInv* inverter;
		TCriticalSection* cs;
		bool isConnect;
		//! ����� ������� ����� ����������� ��������� ��������� ������ 500��
		rotationThread *testThread;
		bool mrs;
		void OnProtocol(AnsiString _msg);
};
//------------------------------------------------------------------------------
class rotationThread: public TThread
{
	protected:
		void __fastcall Execute();
	public:
		__fastcall rotationThread(CInv* _inv,TCriticalSection* _cs);
		void Stop();
	private:
		CInv* inverter;
		TCriticalSection* cs;
		bool isStop;
};
extern Inverter *frConverter;
//------------------------------------------------------------------------------

#endif


