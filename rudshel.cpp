// ---------------------------------------------------------------------------

#pragma hdrstop

#include "rudshel.h"
#include "Protocol.h"

// ---------------------------------------------------------------------------

#pragma package(smart_init)

_LAN10M8PCI::_LAN10M8PCI()
{
	errorCode = 0;

	opened = false;

	int packetSize = 2020;
	int packetCount = 2;
	quantFreq = (float)(25 * 1e6);
	bufferSize = packetSize * packetCount;
	data = new short[bufferSize];
}

_LAN10M8PCI::~_LAN10M8PCI()
{
	if (opened)
		close();
	delete[]data;
}

bool _LAN10M8PCI::checkBoard(const int& baseAddress)
{
	if (baseAddress < 1)
		return false;

	// �������� ������� ��� ������������ �� ����������
	hIRQEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	// ��������� �������
	LAxFactory = (IFactory*)LAxClient.LoadRegistered(CompanyNameDRV,
		ProductNameDRV, VersionNameDRV, DEVICE_NAME_DEFAULT); // ,
	// L"StaticFactory");
	if (LAxFactory == 0)
	{
		errorCode = -10;
		close();
		return false;
	}
	// �������� ��������� ��������
	pADC = (IADCDevice*)LAxFactory->Create((wchar_t *)"IADCDevice", 0);

	if (pADC == 0)
	{
		close();
		return false;
	}
	errorCode = pADC->Setup(baseAddress,0,0,0);
	if (errorCode <= 0)
	{
		close();
		return false;
	}
	Sleep(250);
	errorCode = pADC->Setup(baseAddress, // ����� �����
		1,
		1,
		hIRQEvent);
	if (errorCode <= 0)
	{
		close();
		return false;
	}

	opened = true;

	return true;
}

bool _LAN10M8PCI::initSettings(const acquireSettings& settings)
{
	// �������������� ��������� ���������� ���������
	ADCParametersMEMORY1 a;

	int bsize = settings.measureSize * settings.sensorCount *
		settings.strobesPerPacket;
	if (bsize != bufferSize)
	{
		bufferSize = bsize;
		delete[]data;
		data = new short[bufferSize];
	}

	a.m_nStartOf = ADCPARAM_START_COMP; // ������ �� �����������
	a.m_fFreq = (float)(settings.quantFrequency * 1.0e6);
	// ������� �������������, ��
	a.m_nPacketSize = settings.measureSize; // ������ �����
	a.m_nPacketNumber = settings.sensorCount * settings.strobesPerPacket;
	// ���������� �����
	a.m_nBeforeHistory = 0; // ������ �����������

	// ��������� ��� ����� ������� ������ �����������, �������� �� ��,
	// ��� �� ����� ���� ������������ ������ ���� �����
	a.m_nDelta[0] = 0; // �������� 0-�� ������
	a.m_nGain[0] = settings.ampGain; // �. �������� 0-�� ������
	a.m_nDelta[1] = 0; // �������� 1-�� ������
	a.m_nGain[1] = settings.ampGain; // �. �������� 1-�� ������

	// ������� ����������� ����������
	a.m_nControl = ADC_CONTROL_SYNC_TTL | // �����-��� �� �����. ���������
		// ADC_CONTROL_SYNC_CH0 |
		// ADC_CONTROL_DIFS |       	// ������ ���������� ������
		ADC_CONTROL_DIF0 | ADC_CONTROL_DIF1;

	if (settings.syncType == SYNC_FRONT)
		a.m_nControl |= ADC_CONTROL_SYNC_FRONT; // ������������� �� ������
	else
		a.m_nControl |= ADC_CONTROL_SYNC_DECLINE; // ������������� �� �����

	a.m_nSyncLevel = settings.syncLevel; // ������� �������������
	a.m_nSyncGain = 1; // ����������� �������� ������� �������������
	a.m_nStartDelay = settings.startDelay; // ����������� �������� ��� ������

	// � ���� ���������� ������� ������ ������� ������������� ����� ������ Init
	float freq;

	// �������� ��������� - ����� ��� ������� ������������ �������� �� ��������� ������
	int e1 = 1024;
	int e2 = 1024;
	errorCode = pADC->Init(ADC_INIT_MODE_CHECK, &a, &freq);
	e1 = errorCode;
	if (errorCode <= 0)
	{
		close();
		return false;
	}
	/*
	 ProtocolForm->SendToProtocol("������� " + FloatToStr(a.m_fFreq)
	 + " ������ ������ "	+ IntToStr(a.m_nPacketSize)
	 + " ���������� ����� " + IntToStr(a.m_nPacketNumber)
	 + " ������ ������ ����� " + IntToStr(bufferSize) );
	 */
	errorCode = pADC->Init(ADC_INIT_MODE_INIT, &a, &freq);
	e2 = errorCode;
	if (errorCode <= 0)
	{
		close();
		return false;
	}

	float range;
	errorCode = pADC->Get(ADC_GET_RANGE_BIPOLAR, &range);
	if (errorCode <= 0)
	{
		close();
		return false;
	}
	voltRange = (double)range;

	errorCode = pADC->Get(ADC_GET_MAXAMP, &intRange);
	if (errorCode <= 0)
	{
		close();
		return false;
	}

	int datasize;
	errorCode = pADC->Get(ADC_GET_DATASIZE, &datasize);
	int databits;
	errorCode = pADC->Get(ADC_GET_DATABITS, &databits);

	// ProtocolForm->SendToProtocol("������ ������ �������� � ������ " + IntToStr(datasize)
	// + " ����������� ��� �������������� "	+ IntToStr(databits)
	// + " ������� �� INIT" + FloatToStr(freq));

	opened = true;
	return true;
}

short* _LAN10M8PCI::yield()
{
	pADC->ClearInterrupt();
	errorCode = pADC->Start();
	if (errorCode <= 0)
	{
		close();
		return (NULL);
	}
	if (WaitForSingleObject(hIRQEvent, RUDSHEL_WAIT_TIMEOUT) == WAIT_OBJECT_0)
	{
		errorCode =
			pADC->GetData(ADC_DATA_MODE_CONVERT2INT16 | ADC_DATA_MODE_DATACH0,
			data, bufferSize, 0);
		if (errorCode <= 0)
		{
			close();
			return (NULL);
		}
		pADC->ClearInterrupt();
	}
	else
	{
//		errorCode =
//			pADC->GetData(ADC_DATA_MODE_CONVERT2INT16 | ADC_DATA_MODE_DATACH0,
//			data, bufferSize, 0);
		// ����� ����������
		pADC->ClearInterrupt();
		// ��������� ��������������
		pADC->Stop();
		pr("_LAN10M8PCI::yield: �� ��������� �������");
		return (NULL);
	}
	return (data);
}

void _LAN10M8PCI::close()
{
	if(!opened)
		return;
	opened = false;
	if (pADC)
	{
		pADC->Stop();
		pADC->Release();
		pADC = NULL;
	}
	LAxClient.Free();
	if ((int)hIRQEvent > 0)
		CloseHandle(hIRQEvent);
}

void _LAN10M8PCI::Test()
{
	int psize;
	int *packet;
	String str = "";
	errorCode = pADC->Get(ADC_GET_PACKETLIST, &packet);
	errorCode = pADC->Get(ADC_GET_PACKETLIST_SIZE, &psize);

	for (int i = 0; i < psize; i++)
		str += IntToStr(*(packet + i)) + " ";

	TPr::pr("PacketList " + str);
	// ------------------
	String str2 = "";
	int size;
	int *sizelist;
	errorCode = pADC->Get(ADC_GET_SIZELIST, &sizelist);
	errorCode = pADC->Get(ADC_GET_SIZELIST_SIZE, &size);

	for (int i = 0; i < size; i++)
		str2 += IntToStr(*(sizelist + i)) + " ";

	TPr::pr("SizeList " + str2);

}

void _LAN10M8PCI::ExternalStart()
{
	pADC->ClearInterrupt();
	errorCode = pADC->Start();

	if (errorCode <= 0)
	{
		close();
		Application->MessageBoxW(L"����� ������ ����� ����������!",
			L"������", MB_OK);
	}
}

void _LAN10M8PCI::ExternalStop()
{
	pADC->ClearInterrupt();
	pADC->Stop();
}
void _LAN10M8PCI::pr(AnsiString _msg)
{
	TPr::pr(_msg);
}

