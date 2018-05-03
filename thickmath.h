// ---------------------------------------------------------------------------

#ifndef thickmathH
#define thickmathH

#include <vector>

#include "tubefile.h"
#include "gsl/gsl_spline.h"

// ���������� ����������� ��� ������ ������� ���-�� ���������� �� ���
#define MININUM_PEAKS_COUNT 	(2)

#define THICKMATH_DLL			( L"libthickmath.dll" )

#define UNDETECTED_THICKNESS	((double)(6.0))

#define MAX_THICKNESS           ((double)(6.0))
#define MIN_THICKNESS           ((double)(2.0))

#define PROBE_PULSE_LENGTH		(60)

// ------------------------------------------------------------------------------
// ! ������������ ���� ��������� ��������� ������������� ���������
enum th_status
{
	TH_OK=0, // ������� ������ ����������
		TH_EXTREMUMS_NOT_FOUND=1, // ���������� ��� �� ����������
		TH_GREATER_THAN_MAX=2, // ������ ��� ������ maxThickness
		TH_LESS_THAN_MIN=3, // ������ ��� ����� minThickness
		TH_NOT_ENOUGH_INFO=4, // ������������ ������ ��� �������
		TH_BIG_DIFFERENCE=5, // ������� ����� ������ ������ �����������
		TH_SMALL_MAXIMUM=6, // ��������� ��������� � �������� �� �������������
		TH_BIG_ENERGY=7, // ������� ������ �������� ������
		TH_SMALL_ENERGY=8, // ������� ������ ������� ������
		TH_MAXIMUM_TO_ENERGY=9, // ��������� ��������� � ������� ���� ���������
		TH_MAXIMUM_PEAKS=10, // ���������� ����� ������ �������������
		TH_DJ=11
};

enum type
{
	maximum,minimum
};

// ! ���������, ����������� ��������� ������� ���
struct extremum
{
	// ! �������� (�������������� ���������� ����������), �������� � �������� ���
	int32_t x;
	// ! �������� (������������ ���������� ����������), �������� � ��������� �� ������ �������
	double y;
	// ! ��� ���������� - �������� ��� �������
	enum type type;
};

// ------------------------------------------------------------------------------
// ! ����������� ����� ��������� ���������
class mathematics
{
protected:
	// ��������� �������� - ���������� MathSettings
	// ! ��������
	uint32_t precision;
	// ! ����������� �������������� �������
	double minThickness;
	// ! ����������� ����� ����� ������������ �������
	int minPeaksCount;

	// ! ������������ � � � ��� ��������
	RThickness::calibrationCoefficients calibCoeffs[MAX_SENSOR_COUNT];
	// ! ������ ����������� ������� �� ������� �������
	double minEnergy[MAX_SENSOR_COUNT];
	// ! ������ ������������ ������� ��� ������� �������
	double maxEnergy[MAX_SENSOR_COUNT];
	// ! ������ ��������� ��������� � ������
	double maxToMin[MAX_SENSOR_COUNT];
	// ! ������ ��������� ��������� � �������
	double energyToMax[MAX_SENSOR_COUNT];
	// ! ������ ������������� ���������� �����
	int maxPeaks[MAX_SENSOR_COUNT];
	int djProcent[MAX_SENSOR_COUNT];
	double djIndex[MAX_SENSOR_COUNT];

public:
	// ! ������� ������ ��������� (-��) �� ���
	// ! @param y[] ������ ����� ���
	// ! @param Ny ����� ������� ����� ���
	// !	@param x_peaks[] �������� � ��������� ����� (����������� ������ �������)
	// ! @param y_peaks[] �������� Y ��������� ����� (����������� ������ �������)
	// ! @param *NPeaks ����� ��������� ����� (����������� ������ �������)
	// ! @param  sensorNo ����� �������
	virtual void find_peaks(const double y[],
		const int32_t Ny,
		int32_t x_peaks[],
		double y_peaks[],
		int32_t *Npeaks,
		int sensorNo)=0;

	// ! @brief ������� ����������� ������� �� ����� �������������, ���������� ������ �������������
	// ! @param  x_peaks[] ������ ��������� � �����
	// ! @param  y_peaks[] ������ �������� �����
	// ! @param  NPeaks ����� �����
	// ! @param  thickness ��������� ������� (����������� ������ �������)
	// ! @param  sensorNo ����� �������
	// ! @param  energy ������� �������
	virtual th_status thickness_detect(const int32_t x_peaks[],
		double y_peaks[],
		const int32_t Npeaks,
		double* thickness,
		int sensorNo,
		double energy,
		char* _data,
		int _data_size,
		double* dj)=0;

	// ! ������ ��������� ��� ���������� - ����������� �� �� MathSettings
	void setParameters(RThickness::MathSettings ms);
	// ! ������������ �������������� �������
	double maxThickness;
};

// ------------------------------------------------------------------------------
// ! ���������� �� ������ GAK (������� ��� ����, ���� ��������� ����� ����)
class mathGAK : public mathematics
{
public:
	// ! ����������� ������� �� ����
	mathGAK(RThickness::MathSettings ms);
	// ! ���������������� ������� ������ ���������
	void find_peaks(const double y[], const int32_t Ny,
		int32_t x_peaks[],double y_peaks[],
		int32_t *Npeaks,int sensorNo);
	// ! ���������������� ������� ������� ������� � ������ ������� �������������
	virtual th_status thickness_detect(
		const int32_t x_peaks[],
		double y_peaks[],
		const int32_t Npeaks,
		double* thickness,
		int sensorNo,
		double energy,
		char* _data,
		int _data_size,
		double* dj);
};

// ------------------------------------------------------------------------------
// ! ���������� �� ������ EKE (������� 1 ���, ����������� ����������� �� ������� � ����.)
class mathEKE : public mathematics
{
private:
	bool computeDJ(char* _data,int _size,int _sensor,double* _dj);
public:
	// ! ����������� ������� �� ���
	mathEKE(RThickness::MathSettings ms);
	// ! ���������������� ������� ������ ���������
	void find_peaks(const double y[], const int32_t Ny,
		int32_t x_peaks[],double y_peaks[],
		int32_t *Npeaks,int sensorNo);
	// ! ���������������� ������� ������� ������� � ������ ������� �������������
	virtual th_status thickness_detect(const int32_t x_peaks[],double y_peaks[],
		const int32_t Npeaks,double* thickness,
		int sensorNo,double energy,char* _data,
		int _data_size,double* _dj);
};

// ------------------------------------------------------------------------------
// ! �������� "������� ��� - ������� � ��"
double adc2mm(const double adc, const double a, const double b);
// ! �������� "������� � �� - ������� ���"
double mm2adc(const double mm, const double a, const double b);
// ! ��������� ����������
void medianfilter(double* signal,double* result,int N);

void join_probe(const sample_t signal[],sample_t mixed[],
	int32_t Nsignal,int32_t offset);

// ������� - ������ �� dll c �������� ���

typedef(*__alloc_spline)(int32_t*y,
	int32_t Ny,
	gsl_interp_accel**g_accel,
	gsl_spline**g_spline);

typedef(*__free_spline)(gsl_interp_accel*accel_ptr,gsl_spline*spline_ptr);

typedef void(*__envelope)(int32_t*y,
	int32_t Ny,
	double * curve,
	gsl_interp_accel*accel_ptr,
	gsl_spline*spline_ptr);

typedef int(*__xcorr)(const int8_t data[],
	int32_t acf[],
	int32_t N);

// int opt_thickness_find( const sample_t data[], const int32_t N,
// double *thickness, int32_t *offset );

#endif
