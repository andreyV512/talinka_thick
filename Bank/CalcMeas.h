//---------------------------------------------------------------------------
#ifndef CalcMeasH
#define CalcMeasH
//---------------------------------------------------------------------------
#include "uCFFT.h"
#include "Meas.h"
class CalcMeas
{
private:
	void computeAcf(Meas* _meas);
	void computeAcfR(Meas* _meas);
	void computeAcfG(Meas* _meas);
	void computeThickness(Meas* _meas);
	bool RagACF;
	// ! ������ �� �����, �������������� ��� �� ����
	CFFT* FFT;
	// ! �������� ����� ���
	__envelope envelope;
	// ! ������ ��� � dll �� ����
	__xcorr dll_xcorr;
	// ! �������������� ������, �� �������� ���� �������� ���
	__alloc_spline alloc_spline;
	// ! ������������ ������, �������� �������
	__free_spline free_spline;

	// ! ����������� ���������� ��������� ��� ��� ���������� ���������
	void __fastcall findPeaks(Meas* _meas);
	// ! ������ �������������� ����� - ������ �������� � ������� �������
	std::vector<mathematics*>maths;

	// ! ���. ������: 0 = GAK, 1 = EKE
	RThickness::mathLogic logic;
	TIniFile* ini;
public:
	CalcMeas(bool _RagACF,RThickness::MathSettings _msettings,TIniFile* _ini);
	~CalcMeas(void);
	void __fastcall Exec(Meas* _meas);
};

#endif
