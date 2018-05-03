// ---------------------------------------------------------------------------

#ifndef tubefileH
#define tubefileH

#include <vcl.h>
#include <vector>
#include <deque>

// ����������� ��������� ���������� �������� �� ���������������
// � ��������� ����� ���������� ������������
#define		MAX_SENSOR_COUNT			(6)
typedef int8_t sample_t;
/* � ��������� ����� ������������ 8-��������� ��� */

namespace RThickness
{
	// ! @brief ��������� ������������� ������������� (�������� "������� ��� - �������� �������")
	// ! @brief ������� �������������� �� ������� Y = a * X + b, ��� Y - ������� � ��,
	// ! X - ����� �������� ��� ����� ����������� ���
	struct calibrationCoefficients
	{
		calibrationCoefficients() : a(0.066),b(-0.069)
		{
		}
		calibrationCoefficients(double A,double B) : a(A),b(B)
		{
		}
		// ! �������� ���������
		double a;
		// ! �������� ����������� ������
		double b;
	};

	// ������ �������� ������� �����
	enum mathLogic
	{
		GAK=0,
		EKE=1
	};

	// ! ����� �������������� �������� ��� ������� �����
	class MathSettings
	{
	public:
		// ! ����������� ������ ��� �������� �� ���������
		MathSettings();
		// ! ����������� ������ ��� ��������, ������ �� ���������� ����� ��������
		MathSettings(const uint8_t& SensorCount);

		void setSensorCount(const uint8_t& SensorCount);
		void setPrecision(const uint32_t& Precision);
		void setCalibrationCoefficients(const uint8_t& sensorNum,
			const calibrationCoefficients& Value);
		void setMinEnergy(const uint8_t& sensorNum,double value);
		void setMaxEnergy(const uint8_t& sensorNum,double value);
		void setMaxToMin(const uint8_t& sensorNum,double value);
		void setEnergyToMax(const uint32_t& sensorNum,double value);
		void setMaxPeaks(const uint32_t& sensorNum,int value);
		void setDJProcent(const uint32_t& sensorNum,int value);
		void setDJIndex(const uint32_t& sensorNum,double value);

		void setMinMaxThicknesses(const double& MinThickness,
			const double& MaxThickness);
		void setMinPeaksCount(const uint8_t& minpeaks);
		void setSmartMaths(const bool& smrt);
		void setSmartBegin(const int8_t& smrtBegin);
		void setSmartEnd(const int8_t& smrtEnd);
		void setLogics(int value);

		bool operator==(const MathSettings& Settings);

		const calibrationCoefficients getCalibrationCoefficients(const uint8_t& sensorNum);
		const double MinEnergy(const uint32_t &sensorNum);
		const double MaxEnergy(const uint32_t &sensorNum);
		const double MaxToMin(const uint32_t &sensorNum);
		const double EnergyToMax(const uint32_t &sensorNum);
		const int MaxPeaks(const uint32_t &sensorNum);
		const int DJProcent(const uint32_t &sensorNum);
		const double DJIndex(const uint32_t &sensorNum);

		const inline uint32_t Precision()
		{
			return precision;
		}
		const inline uint8_t SensorCount()
		{
			return sensorCount;
		}
		const inline double MinThickness()
		{
			return minThickness;
		}
		const inline double MaxThickness()
		{
			return maxThickness;
		}
		const inline int MinPeaksCount()
		{
			return minPeaksCount;
		}
		const inline bool IsSmartMaths()
		{
			return smartMaths;
		}
		const inline int SmartBegin()
		{
			return smartBegin;
		}
		const inline int SmartEnd()
		{
			return smartEnd;
		}
		inline mathLogic CurrentLogic()
		{
			return logic;
		}

	private:
		// ! ���������� �������� � ��������� �������������
		uint8_t sensorCount;

		// ! @brief ����������� ���������� ���������� ����� ������ �� ���,
		// ! ��� ������� ������ ������������� ��� �����������, �
		// ! ������������ ���������� ����������� �������
		uint32_t precision;

		// ! @brief ������������� ������������ ��� ������� �� ��������
		// ! (������� ������ �� ����� ������, �.�. ������� ������
		// ! �������� ������� � �����)
		calibrationCoefficients calibCoeffs[MAX_SENSOR_COUNT];
		// std::vector< calibrationCoefficients >  calibCoeffs;
		// ! ����������� ������� - ������������ ��� ������� �������
		double minEnergy[MAX_SENSOR_COUNT];
		// ! ������������ ������� - ������������ ��� ������� �������
		double maxEnergy[MAX_SENSOR_COUNT];
		// ! ��������� ��������� � �������� - ������������ ��� ������� �������
		double maxToMin[MAX_SENSOR_COUNT];
		// ! ��������� ������� � ���������
		double energyToMax[MAX_SENSOR_COUNT];
		// ! ������������ ���������� �����
		int maxPeaks[MAX_SENSOR_COUNT];
		int djProcent[MAX_SENSOR_COUNT];
		double djIndex[MAX_SENSOR_COUNT];

		// ! ����������� ������������ ������� � ��
		double minThickness;
		// ! ����������� ������������ ������� � ��
		double maxThickness;
		// ! ����������� ����� ����� ��� ��������
		int minPeaksCount;
		// ! ������������ �� ����������� ����������
		bool smartMaths;
		// ! ��������� ����� �������� ����� ����������
		int smartBegin;
		// ! �������� ����� �������� ����� ����������
		int smartEnd;
		// ! ������� ��� ������
		mathLogic logic;
	};

}; // namespace

#endif
