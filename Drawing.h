//---------------------------------------------------------------------------

#ifndef DrawingH
#define DrawingH

#include "Classes.hpp"
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IniFiles.hpp"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "Series.hpp"
#include <ComCtrls.hpp>
#include <windows.h>
#include "IniFiles.hpp"
#include <ImgList.hpp>

#include "Global.h"
//---------------------------------------------------------------------------
//! ����� �� ��������� ����������� �������� �� �����
class DrawResults
{
private:
	//! ���� ������
	static TColor Brack;
	//! ���� ������� ������
	static TColor Class2;
	//! ���� ������, ������� �����
	static TColor Good;
	//! ���� ��������������� ���������
	static TColor NotMeasured;

public:
	//! ������ ������� - [0] - ����� �����, [1] - ����� ������ 2 � �.�.
	static DynamicArray <double> borders;
	//! ����������� ������ �������
	static int min_good_length;
	//! ������� �� ����� (����, �����, ����� 2)
	static String decision;
	//! ���� ��� ������ �����
	static short cut1,cut2;
	//! ���� ���������� (���� -������� � �.�.)
	static TColor ResultColor;
	//! ����������� ������� �� ���� �����
	static double min_thickness;
	//! ���� � ����������� ��������
	static int min_thickness_zone;

	//! �����������
	DrawResults(TIniFile *_ini);
	//! ���������� ���� ��������� (����, �������, �������� - ���� ������)
	static TColor GetColor(double measure);
	//! ��������� ������� �� ���� ����� � ��������� ���� ������
	static void MakeDecision(std::vector<double> thickness);
	static bool IsBrak(double measure);


};

	TColor DrawResults::Brack = clRed;
	TColor DrawResults::Class2 = clBlue;
	TColor DrawResults::Good = clGreen;
	TColor DrawResults::NotMeasured = clLtGray;
	DynamicArray <double> DrawResults::borders;
	int DrawResults::min_good_length = 1;
	short DrawResults::cut1 = 0;
	short DrawResults::cut2 = 0;
	String DrawResults::decision = "";
	TColor DrawResults::ResultColor = clWhite;
	double DrawResults::min_thickness = -1;
	int DrawResults::min_thickness_zone = -1;

#endif
