// --------------------------------------------	-------------------------------

#pragma hdrstop
#include <IniFiles.hpp>

#include "WorkMode.h"
#include "Main.h"
#include "Protocol.h"
//#include "LCARD502.h"
#include "A1730.h"
// ---------------------------------------------------------------------------

#pragma package(smart_init)

// ---------------------------------------------------------------------------

int centralizerSleep = 500; // ����� �������� ����� ������������� ������
// �������
int SleepTemp = 750;

// -----------------------------------------------------------------------------
__fastcall WorkThreadClass::WorkThreadClass(RawStrobes* _rawStrobes,
	TIniFile* _ini, ADCBoards* _adcboards)
{
	rawStrobes = _rawStrobes;
	ini = _ini;
	adcboards = _adcboards;
}

__fastcall WorkThreadClass::~WorkThreadClass(void)
{
}

void __fastcall WorkThreadClass::Execute()
{
	a1730->ClearLatchError();
	pr("WorkThreadClass");
	a1730->AlarmCycleOn(false);
	a1730->SetAlarm(false);
	NameThreadForDebugging("WorkThread");
	a1730->oPCHPOW->Set(true);
	adcboards->initSettings(&Globals_adcSettings);
	pr("���������������� ������ ������");
}

void WorkThreadClass::WorkMode(void)
{
	DataAcquirer* da0 = NULL;
	DataAcquirer* da1 = NULL;
	// da0 = new DataAcquirer(adcboards->board0, rawStrobes);
	// da1 = new DataAcquirer(adcboards->board1, rawStrobes);
	// Sleep(2000);
	// return;

	AnsiString a;
	a1730->SetAlarm(true);
	stext2 = "�������� ������";
	Synchronize(UpdateMainForm);
	pr("-------------------------------");
	pr("�����: " + TimeToStr(Time()));
	pr("����� �����, ����� ������");
	int abc = 0;
	result = true;
	// DataAcquirer* da0 = NULL;
	// DataAcquirer* da1 = NULL;
	AnsiString reason;
	while (true)
	{
		// reason = "���� ������";
		// break;
		if (!a1730->iCC->Get())
		{
			reason = "�� �������� ����� ����������";
			break;
		}
		// ���� ����
		stext2 = "���� ������ ����";
		pr(stext2);
		Synchronize(UpdateMainForm);
		reason = a1730->iCYCLE->Wait(true, 600000);
		if (reason != "Ok")
		{
			if (reason == "�� ���������")
				reason = "�� ��������� ������� ����!";
			break;
		}
		pr("�������� �������������� ����");
		// �������� �������������� ����
		a1730->AlarmCycleOn(true);
		pr("��������� ����������");
		a1730->oSHIFT->Set(true);

		stext2 = "�������� ����� �� ����� � ��������� (������ \"����������\")";
		Synchronize(UpdateMainForm);
		reason = a1730->iREADY->Wait(true, INFINITE);
		if (reason != "Ok")
			break;
		pr("������: ���� ������ \"����������\" �� ��");
		pr("����� ����������");
		a1730->oSHIFT->Set(false);

		// �������� �������� ������
		stext2 = "�������� �������� ����� ��������";
		Synchronize(UpdateMainForm);
		pr(stext2);

		if (!frConverter->setParameterSpeed(Globals_defaultRotParameter,
			ini->ReadInteger("Type_" + Globals_typesize.name, "InSpeed", 20)))
		{
			reason = "�� ������� ��������� �������� ��������!";
			break;
		}

		if (!frConverter->startRotation())
		{
			reason = "�� ������� �������� ��������";
			break;
		}
		reason = a1730->iPCHRUN->Wait(true, 6000);
		if (reason != "Ok")
		{
			if (reason == "�� ���������")
				reason = "�� ������ ������������!";
			break;
		}
		Sleep(500);
		pr("������� ������� ����������");
		a1730->oSOLPOW->Set(true);
		Sleep(1000);
		pr(ThickSolenoid->GetUIR());
		if (!ThickSolenoid->OkU())
		{
			reason = "���������� ���������� ��� ��������� - ������!!!";
			a1730->oSOLPOW->Set(false);
			break;
		}
		if (!ThickSolenoid->OkResist())
		{
			reason = "������������� ���������� �������� - ��������!!!";
			a1730->oSOLPOW->Set(false);
			break;
		}
		pr("���������� ������ ������");
		a1730->oWORK->Set(true);
		pr("�������� �����");
		da0 = new DataAcquirer(adcboards->board0, rawStrobes);
		da1 = new DataAcquirer(adcboards->board1, rawStrobes);
		Synchronize(ClearCharts);
		stext2 = "���� ������ ��������";
		pr(stext2);
		Synchronize(UpdateMainForm);

		reason = a1730->iCONTROL->Wait(true, INFINITE);
		if (reason != "Ok")
			break;
		pr("��������� ���������");
		a1730->oMEAS->Set(true);
		stext2 = "��������� ���� ������";
		Synchronize(UpdateMainForm);
		pr("�������� ������� ������������");
		a1730->oSCANPOW->Set(true);
		rawStrobes->StartTick(GetTickCount());
		pr("������ ������ ������");
		a1730->SetOnFront(AddTickStrobe);
		pr("���� ������� ������");
		reason = a1730->iSTROBE->Wait(true, 5000);
		if (reason != "Ok")
		{
			if (reason == "�� ���������")
				reason = "�� ��������� ������� ������";
			break;
		}
		if (!frConverter->setParameterSpeed(Globals_defaultRotParameter,
			ini->ReadInteger("Type_" + Globals_typesize.name, "WorkSpeed", 40)))
		{
			reason = "�� ������� ��������� ������� �������� ��������!";
			break;
		}
		stext2 = "��������� ���� ������ (���� ���������� ������� \"��������\")";

		// ������� �������� ���� ���

		Synchronize(UpdateMainForm);

		reason = a1730->iCONTROL->Wait(false, 40000);
		if (reason != "Ok")
		{
			if (reason == "�� ���������")
				reason = "�� ��������� ������ ������� \"��������\"!";
			break;
		}
		pr("��������� ������ ������");
		a1730->SetOnFront(NULL);
		pr("��������� �������������� ������");
		a1730->SetAlarm(false);

		// ��� ���� ���������� ���������� - ������ � ����� ����� ���� �� ������
		// ������ �� ���������

		if (!frConverter->stopRotation())
		{
			reason = "�� ������� ���������� ��������";
			break;
		}
		reason = "Ok";
		break;
	}
	/*
	 pr("1111111111111111111111111111111");
	 a = "-40 getchVoltage()=";
	 a += ThickSolenoid->getchVoltage();
	 pr(a);
	 rawStrobes->StopTick(GetTickCount());
	 a = "-41 getchVoltage()=";
	 a += ThickSolenoid->getchVoltage();
	 pr(a);
	 pr("1111111111111111111111111111111");
	 a = "-42 getchVoltage()=";
	 a += ThickSolenoid->getchVoltage();
	 pr(a);
	 */
	frConverter->stopRotation();
	rawStrobes->StopTick(GetTickCount());
	for (; ;)
	{
		if (rawStrobes->IsComplete())
			break;
		Sleep(400);
	}
	pr("WorkThreadClass::WorkMode: ��������� ���������� rawStrobes");
	// ����� ����� ����, ���� ���� ��� �����
	if (da0 != NULL)
	{
		delete da0;
		da0 = NULL;
	}
	if (da1 != NULL)
	{
		delete da1;
		da1 = NULL;
	}
	pr("��������� ������ ������ � �����");
	a1730->SetOnFront(NULL);
	pr("��������� �������������� ������");
	a1730->SetAlarm(false);
	a1730->AlarmCycleOn(false);
	// ������� ����������� �������
	pr("����� ��� �������");
	a1730->oSOLPOW->Set(false);
	a1730->oSHIFT->Set(false);
	a1730->oRESULT->Set(false);
	// a1730->oWORK->Set(false);
	a1730->oSCANPOW->Set(false);
	a1730->oMEAS->Set(false);
	if (reason == "Ok")
	{
		Sleep(1000);
		a1730->oWORK->Set(false);
		stext1 = "����� \"������\" �������� �������";
		stext2 = "";
		result = true;
	}
	else if (reason == "�������� �������������")
	{
		a1730->oWORK->Set(false);
		stext1 = "����� \"������\" ������� �������������";
		frConverter->stopRotation();
		stext2 = reason;
		result = false;
	}
	else
	{
		a1730->oWORK->Set(false);
		stext1 = "����� \"������\" �������� � �������!";
		frConverter->stopRotation();
		a1730->oPCHPOW->Set(false);
		stext2 = reason;
		result = false;
	}
	pr(stext1);
	pr(stext2);
	Synchronize(UpdateMainForm);
}

// -----------------------------------------------------------------------------
void __fastcall WorkThreadClass::ClearCharts()
{
	MainForm->ClearCharts();
}

void __fastcall WorkThreadClass::UpdateMainForm()
{
	MainForm->StatusBarTop->Panels->Items[1]->Text = stext1;
	MainForm->StatusBarTop->Panels->Items[2]->Text = stext2;
	MainForm->StatusBarTop->Refresh();
	MainForm->work_result = result;
}

void WorkThreadClass::pr(AnsiString _msg)
{
	TPr::pr(_msg);
}

void __fastcall WorkThreadClass::AddTickStrobe(unsigned int _tick)
{
	rawStrobes->AddTickStrobe(_tick);
}
