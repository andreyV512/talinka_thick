// ---------------------------------------------------------------------------
#pragma hdrstop
#include "Solenoid.h"
#pragma package(smart_init)
#include "LCARD502.h"

Solenoid::Solenoid(TIniFile* _ini)
{
	chAmperage = 0;
	chVoltage = 1;
	AlarmLevel = _ini->ReadFloat("Solenoid", "ResistSolenoid", 91.0);
	AlarmULevel = _ini->ReadFloat("Solenoid", "VoltageSolenoid", 270);
	DifULevel = _ini->ReadFloat("Solenoid", "DifVoltageSolenoid", 20);
	Devider = _ini->ReadFloat("OtherSettings", "Devider", 74.0);
}

Solenoid::~Solenoid(void)
{
}

// ---------------------------------------------------------------------------
double Solenoid::getAmperage()
{
	vector<double>Vec = lcard->getFrameValue();
	double I = Vec[chAmperage];
	return I = (I - 2.5) * 10;
}

double Solenoid::getVoltage()
{
	vector<double>Vec = lcard->getFrameValue();
	double U = Vec[chVoltage];
	U = U * Devider;
	return U;
}

double Solenoid::getResist()
{
	double i = getAmperage();
	double u = getVoltage();
	// проверка на отсутствие напряжения
	if (u < 230)
		return (AlarmLevel + 1);

	else
		return (u / i);
}

bool Solenoid::OkResist()
{
	return (getResist() < AlarmLevel);
}

bool Solenoid::OkU()
{
	return ((getVoltage() < DifULevel + AlarmULevel) && (getVoltage() >
		AlarmULevel - DifULevel));
}
AnsiString Solenoid::GetUIR(void)
{
	double i = getAmperage();
	double u = getVoltage();
	double R = (double)(u / i);
	AnsiString ret;
	ret.printf("U=%.3lf I=%.3lf R=%.3lf", u, i, R);
	return (ret);
}
