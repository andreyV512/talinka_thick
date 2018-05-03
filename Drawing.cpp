//---------------------------------------------------------------------------


#pragma hdrstop

#include "Drawing.h"
#include "Protocol.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

DrawResults::DrawResults(TIniFile *_ini)
{
	borders.set_length(2);
// ������ �����, ������� ����� ����
	Brack = (TColor)_ini->ReadInteger("Color","Brack",0);
	Class2 = (TColor)_ini->ReadInteger("Color","SecondClass",0);
	Good = (TColor)_ini->ReadInteger("Color","Valid",0);
	NotMeasured = (TColor)_ini->ReadInteger("Color","NotMeasured",0);
}
//---------------------------------------------------------------------------

TColor DrawResults::GetColor(double measure)
{
// ���������� ���� ���� � ����������� �� ������� � ���� ����
	if (measure >= Globals_mathSettings->MaxThickness())
		return NotMeasured;
	else if (measure > borders[borders.get_high()])
		return Good;
	else if (measure <= borders[0])
		return Brack;
	else
		return Class2;
}
//---------------------------------------------------------------------------
bool DrawResults::IsBrak(double measure)
{
	return(measure <= borders[0]);
}
void DrawResults::MakeDecision( std::vector<double> thickness )
{
// ��������� ������� �� ���� ����� � ��������� ���� ������
	bool flag=false;		// �������������, ��� ������� ������� ����� ������� 2-�� �������, ���� �������� ����������� ������ �����
	bool class2=false;		// ������� ����� ����� ������� 2-�� �������
	short temp=0;			// ����� �������� ������� � �����
	short tcut1=0; 			// ��������� ������ ���
	cut1=cut2=0;			// ����� �� ��������� ���
	decision="�����";			// ������� �� �������
	// ���� ���� � ����������� �������� �������
	double min = 10e7;
	for (int i = 0; i < (int)thickness.size(); i++)
	{
		if ( thickness[i] < min )
		{
			min = thickness[i];
			min_thickness = thickness[i];
			min_thickness_zone = i+1;
		}
	}
	min_thickness = (double)Math::RoundTo(min_thickness, -2);
}
//---------------------------------------------------------------------------


