//---------------------------------------------------------------------------
#ifndef TypesizeH
#define TypesizeH
#include <System.hpp>
#include <vector.h>
#include <IniFiles.hpp>

//---------------------------------------------------------------------------
class Typesize
{
public:
	// ! ��� �����������
	String name;
	// ! ������� �����(60,73,89)
	int diameter;
	// ! ������ ������� - [0] - ����� �����, [1] - ����� ������ 2 � �.�.
	DynamicArray<double>borders;
	// ! ����������� ������ �������
	int min_good_length;
	// ! ����������� ������������ ������� (��� ����������)
	double min_detected;
	// ! ����������� ������������ ������� (��� ����������)
	double max_detected;
	// ! �������� �������� ������ � ������
	vector<int>workSpeed;
	// ! �������� �������� ������ ��� ����� �����
	vector<int>inSpeed;
	// ! �������� �������� ������ ��� ������ �����
	vector<int>outSpeed;
	// ! �������� ����� ������������ ������� ��������
	int inDelay;
	// ! ����������� �������
	double nominal_thickness;
	int ThicknessDeadZoneStart;
	int	ThicknessDeadZoneFinish;
	// ! ������������� ���������� (������ �� ini � �������)
	void setTypesize(String TypesizeName,TIniFile *ini);
};
#endif
