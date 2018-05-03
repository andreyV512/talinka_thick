// ---------------------------------------------------------------------------

#ifndef ViewTubeDetailsH
#define ViewTubeDetailsH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>

// #include "tubefile.h"
//#include "rtube.h"
#include "Global.h"
#include "Drawing.h"
#include <Menus.hpp>
#include "Result.h"
#include "UTFSpectro.h"
#include "uCFFT.h"

// ---------------------------------------------------------------------------
class TViewTubeDetailsForm : public TForm
{
__published: // IDE-managed Components

	TChart *MeasureChart;
	TSplitter *Splitter1;
	TChart *SourceSignalChart;
	TSplitter *Splitter2;
	TChart *ACFChart;
	TStatusBar *sbACF;
	TStatusBar *sbSource;
	TStatusBar *sbMeasure;
	TRichEdit *rePeaks;
	TBitBtn *bShowRePeaks;
	TCheckBox *cbMedianFilter;
	TBarSeries *Series1;
	TPopupMenu *popupACF;
	TMenuItem *pmDrawMinMaxThickness;
	TSpeedButton *SBSF;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall MeasureChartMouseWheelDown(TObject *Sender,
		TShiftState Shift, TPoint &MousePos, bool &Handled);
	void __fastcall MeasureChartMouseWheelUp(TObject *Sender, TShiftState Shift,
		TPoint &MousePos, bool &Handled);
	void __fastcall MeasureChartKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift);
	void __fastcall ACFChartClickSeries(TCustomChart *Sender,
		TChartSeries *Series, int ValueIndex, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall ACFChartMouseWheelDown(TObject *Sender, TShiftState Shift,
		TPoint &MousePos, bool &Handled);
	void __fastcall ACFChartMouseWheelUp(TObject *Sender, TShiftState Shift,
		TPoint &MousePos, bool &Handled);
	void __fastcall ACFChartKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift);
	void __fastcall ACFChartClickBackground(TCustomChart *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall SourceSignalChartClickBackground(TCustomChart *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall SourceSignalChartKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift);
	void __fastcall SourceSignalChartMouseWheelDown(TObject *Sender,
		TShiftState Shift, TPoint &MousePos, bool &Handled);
	void __fastcall SourceSignalChartMouseWheelUp(TObject *Sender,
		TShiftState Shift, TPoint &MousePos, bool &Handled);
	void __fastcall bShowRePeaksClick(TObject *Sender);
	void __fastcall cbMedianFilterClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall pmDrawMinMaxThicknessClick(TObject *Sender);
	void __fastcall MeasureChartClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall SBSFClick(TObject *Sender);

private: // User declarations

	int curr_zone; // ����� ����, ������� �������
	int curr_sensor; // ����� �������, ������� �������
	int curr_measure; // ����� ���������, ������� �������
	int curr_acf_cur; // ������� �������� ������� ���
	bool filter; // ������� �� ��������� ������

	int Curr_Signal1; // ������ �� ��������� ������� �1
	int Curr_Signal2; // ������ �� ��������� ������� �2
	int divider; // �������� = ����� ����� ������� ���������� ������������

//	std::vector<sample_t>source; // ������ ��������� ��������
//	std::vector<double>acf;
	// ������ �������� ���, ������� ���������� �� �������
	CRListLT<Meas>* measures;
	// ������ ��������� (������), ������� ���������� �� �������
	std::vector<RThickness::CurvePeak>cp; // ������ ��������� ����� ���

//	MathSettings maths; // ����������
	calibrationCoefficients coeffs; // ������������ ���������� �������� � � �

	void PutDataOnCharts(int z, int s, int o);
	// ������ ��� ���� �� ���� ��������
	void ShowPeaks(); // ���������� ���� �� ��������
	void ShowACFCursor(); // ���������� ������ �� ������� ���
	void ShowSignal1(); // ���������� ������ �1 �� ������� ���������� �������
	void ShowSignal2(); // ���������� ������ �2 �� ������� ���������� �������
	void ShowMinMax(); // ������ MinThickness � MaxThickness �� ����� ���
	void ClearStatusBars(); // ������ ������ ���� � ��� � ���������� �������

//	int ACFSize;
	Result* r;
	Meas* cur_meas;
	TIniFile *ini;
	void PutDataOnSpectro(void);
	CFFT* fft;
	TFSpectro* fspectro;
	void SetSpectroBorders(int _BorderLeft,int _BorderRight);
public: // User declarations

	__fastcall TViewTubeDetailsForm(TComponent* Owner, Result* _r,TIniFile* _ini);
	void SendTube(int zone, int sensor);
	// ��������� ����������� �� ������� ����� ����
};

// ---------------------------------------------------------------------------
extern PACKAGE TViewTubeDetailsForm *ViewTubeDetailsForm;
// ---------------------------------------------------------------------------
#endif
