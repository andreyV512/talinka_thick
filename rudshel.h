// ---------------------------------------------------------------------------

#ifndef rudshelH
#define rudshelH

#include <vector>
#include <stdint.h>
#include <windows.h>

#include <IADCDevice.h>
#include <IFactory.h>
#include <DllClient.h>
#include <REGKEY\VT_Drivers.ri>
#include <REGKEY\VT_Library.ri>
#include <ADC_Errors.h>
#include "tubefile.h"

#define DEVICE_NAME_DEFAULT     _T("LAN10M8PCI")    	// �������� ��������
// #define BASE_ADDRESS_DEFAULT    1	           			// ����� �����
#define DRQ_NUMBER_DEFAULT      1               		// ����� ������ ���
#define IRQ_NUMBER_DEFAULT      DRQ_NUMBER_DEFAULT    	// ����� ����������

#define RUDSHEL_WAIT_TIMEOUT			10000			  	// � ��
#define MAX_BOARD_COUNT		(2)

enum RudShelSyncType
{
	SYNC_DECLINE = 0, SYNC_FRONT = 1
};

// ! ���������, ����������� ��������� ����� ������ ������-������ LAn10M8PCI
struct acquireSettings
{
	// ! ����� ������ ��������� (��������, 484, 996 � �.�.)
	int32_t measureSize;
	// ! ���������� ��������
	int32_t sensorCount;
	// ! ������� �������������
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
	RudShelSyncType syncType;
};

// ! ����� �� ������ � ������ ��� ������-������ LAn10M8PCI
class _LAN10M8PCI
{
private:
	// ! ������ ��������� ������ (������ �������� � ��������� * ����� ��������� � ������ * ����� �������� )
	int32_t bufferSize;
	// ! @brief ������� �����
	// ! @deprecated ����� �� ������������, ������� ��� ������ �� ������������ �������������
	float quantFreq;
	// ! �������� ���������� ����������
	double voltRange;
	// ! ������������ ��������, ������� ������������ ����� ������
	int32_t intRange;
	// ! ���� ������� �� �����
	bool opened;

	// ! ������� ��� ������������ �� ����������
	HANDLE hIRQEvent;
	// ! ������, ���������� ������� ������� ��� �������� �������� � ������
	DllClient LAxClient;
	// ! ��������� �� ������ ��������
	IFactory* LAxFactory;
	// ! ��������� �� ������ ����������
	IADCDevice* pADC;

	int32_t errorCode;

	short* data;
	void pr(AnsiString _msg);

public:
	// ! �����������
	_LAN10M8PCI();
	// ! ����������
	~_LAN10M8PCI();

	// ! ��������� ����� ��� ����� - ��������� �������, �������� ��������� ��� ������
	// ! @param baseAddress ����� ����� ������, ���������� �� ������� 0,1
	bool checkBoard(const int& baseAddress);
	// ! @brief ������ ��������� ����� ������, ���������� ��������� ��� ������
	// ! @param ���������� ��������� @link acquireSettings @endlink
	bool initSettings(const acquireSettings& settings);
	// ! �������� ������� - ������ ���� ������������ ������
	short* yield();

	// ! ���������� ��� ��������� ������
	inline int32_t lastError()
	{
		return errorCode;
	}

	// ! ���������� �������� ���������� ���������� ����� (��. ADC_GET_RANGE_BIPOLAR � ������������ ������)
	inline double voltageRange()
	{
		return voltRange;
	}

	// ! ���������� ������������ �������� ����� (��. ADC_GET_MAXAMP � ������������ ������)
	inline int32_t adcRange()
	{
		return intRange;
	}

	// ! ����������, ������� �� ����� ��� ������
	inline bool Opened()
	{
		return opened;
	}
	// ! ������� �����
	void close();

	// ! ����� ����� ������ ������ ����� ��� ������, ���������� ���������, ��� ������
	void Test();
	// ! ������� ����� ����� (��������������)
	void ExternalStart();
	// ! ������� ���� ����� (��������������)
	void ExternalStop();


};

// ---------------------------------------------------------------------------
#endif
