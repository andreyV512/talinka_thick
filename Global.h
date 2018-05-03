// ---------------------------------------------------------------------------

#ifndef GlobalH
#define GlobalH

#include <IniFiles.hpp>
#include "Typesize.h"
#include "CL10M8PCI_SDK2.h"
#include "RThickness.h"
#include "tubefile.h"
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ! ��������� ���� ������-������
extern AcquireSettings Globals_adcSettings;
// ! ��������� ������ ����������
extern Typesize Globals_typesize;
extern double Globals_MaxToMin;
// ! ������������ ���������� ��������
const int Globals_max_sensors=6;
// ! ������������ ���������� ���
extern int Globals_max_zones;
// ! �������� ���������� � ������� �������� �������� �������
extern int Globals_defaultRotParameter;

using namespace RThickness;
extern MathSettings* Globals_mathSettings;

// ---------------------------------------------------------------------------
#endif
