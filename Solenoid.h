// ---------------------------------------------------------------------------
#ifndef SolenoidH
#define SolenoidH
// ---------------------------------------------------------------------------
// ! ����� ������ � �����������
#include <IniFiles.hpp>

class Solenoid
{
public:
	// ! ����������� �� ���������
	Solenoid(TIniFile* _ini);
	~Solenoid(void);
	// ! @brief ����������� � �����������
	// ! �������� �������� ���� ���������
	double getAmperage();
	// ! �������� �������� ���������� ���������
	double getVoltage();
	// ! ���������� �������� ����������� ���������
	double getResist();
	// ! ���������, �� ���������� �� ��������
	bool OkResist();
	bool OkU(void);
	AnsiString GetUIR(void);
	inline int getchVoltage(void)
	{
		return (chVoltage);
	}

private:
	// ! ����������� �������������
	double Devider;
	// ! ����� L-Card, �� ������� ��������� ����� ����
	int chAmperage;
	int bbb[40];
	// ! ����� L-Card, �� ������� ��������� ����� ����������
	int chVoltage;
	// ! ����������� ������� �����������, ���� �������� ������� ��������
	double AlarmLevel;
	double AlarmULevel;
	double DifULevel;

};

#endif
