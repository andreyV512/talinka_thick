//---------------------------------------------------------------------------
#ifndef AcquireSettingsH
#define AcquireSettingsH
#include <System.hpp>
#include <IniFiles.hpp>
class AcquireSettings
{
private:
	AnsiString section;
public:
	// ! ����� ������ ��������� (��������, 484, 996 � �.�.)
	int32_t measureSize;
	// ! ���������� ��������
	int32_t sensorCount;
	// ! ������� ������������� (* 1.0e6)
	float quantFrequency;
	// ! ������� �������������
	int32_t syncLevel;
	// ! ����������� ��������
	int32_t ampGain;
	// ! ����� ������� � 1 ������
	int32_t strobesPerPacket;
	// ! �������� ����� �������� �������������� � ����������
	// ! ������� ���������. ���������� ������ startDelay ��������
	// ! ��� ������������ ������������� ������ ������-������
	int32_t startDelay;
	// ! ��� �������������
	bool syncFront;
	AcquireSettings(void);
	AcquireSettings(TIniFile* _ini);
	void LoadSettings(TIniFile* _ini);
	void SaveSettings(TIniFile* _ini);
};
#endif
