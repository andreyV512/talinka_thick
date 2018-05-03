//---------------------------------------------------------------------------
#pragma hdrstop
#include "A1730_virtual.h"
#include "Protocol.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
A1730_virtual* A1730_virtual::Create(int _DevNum, AnsiString _file_name, TIniFile* _ini,
	bool _ReadOnly)
{
	return (new A1730_virtual(_DevNum, _file_name, _ini, _ReadOnly));
}

A1730_virtual::A1730_virtual(int _DevNum, AnsiString _file_name, TIniFile* _ini, bool _ReadOnly)
{
	cs = new TCriticalSection();
	TIniFile *ini = new TIniFile(_file_name);
	TStringList *sections = new TStringList();
	TStringList *keys = new TStringList();
	ini->ReadSections(sections);
	if (sections->Count == 0)
	{
		AnsiString a = "Signals::Signals: ���� ";
		a += _file_name;
		a += " ���� �� ����������, ���� ����";
		throw(Exception(a));
	}
	for (int i = 0; i < sections->Count; i++)
	{
		AnsiString Sect = sections->Strings[i];
		bool in = Sect.SubString(8, 3) == "IN_";
		if (Sect.SubString(1, 5) == "ACard")
		{
			ini->ReadSection(Sect, keys);
			for (int j = 0; j < keys->Count; j++)
			{
				AnsiString Key = keys->Strings[j];
				AnsiString MapKey = ini->ReadString(Sect, Key, "");
				M.Add(new CSignal(MapKey, in, keys->Strings[j].ToInt(),
					WriteSignals, cs, Wait));
			}
		}
	}
	delete keys;
	delete sections;
	delete ini;
	iPCHA = Find("�� �");
	iCC = Find("���� ����������");
	iPCHRUN = Find("�� RUN");
	iSTROBE = Find("����� ����");
	iCYCLE = Find("����");
	iREADY = Find("����������");
	iCONTROL = Find("��������");

	oPCHPOW = Find("������� ��");
	oSCANPOW = Find("������� ��");
	oSOLPOW = Find("������� ��������");
	oWORK = Find("������");
	oMEAS = Find("���������");
	oSHIFT = Find("����������");
	oSTROBE = Find("�����");
	oRESULT = Find("���������");
}
__fastcall A1730_virtual::~A1730_virtual(void)
{
	delete cs;
}

void A1730_virtual::SetPeriod(int _period)
{
}

CSignal* A1730_virtual::Find(AnsiString _name)
{
	for (int i = 0; i < M.Count(); i++)
	{
		if (M[i]->name == _name)
			return (M[i]);
	}
	AnsiString a = "Signals::Find: ������ ";
	a += _name;
	a += " �� ������";
	throw(Exception(a));
//	return (NULL);
}


void A1730_virtual::WriteSignals(void)
{
}

AnsiString A1730_virtual::Wait(bool _value, CSignal* _signal, DWORD _tm)
{
	return ("Ok");
}


void A1730_virtual::AlarmCycleOn(bool _v)
{
}


void A1730_virtual::SetOnFront(OnFrontDef _OnFront)
{
}

void A1730_virtual::Latchterminate(AnsiString _msg)
{
}

void A1730_virtual::SetAlarm(bool _IsAlarm)
{
}

void A1730_virtual::pr(AnsiString _msg)
{
	TPr::pr(_msg);
}
//---------------------------------------------------------------------------
