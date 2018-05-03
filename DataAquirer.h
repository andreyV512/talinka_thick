// ---------------------------------------------------------------------------
#ifndef DataAquirerH
#define DataAquirerH
// ---------------------------------------------------------------------------
#include "RawStrobes.h"
#include "CL10M8PCI_SDK2.h"

// ! @brief ����� �� ����� ������ � ����� ��� ������-������ LAn10M8PCI-100.
// ! ��������� ���� ������ � �����, ��� ������ �������� ����������� ����� - ������ ������� � DataReceiver
// ! � ���������� ����� �������
class DataAcquirer : public TThread
{
private:
	// ! ����� ����� ��� � ����������
	CL10M8PCI_SDK2* card;
	RawStrobes* rawStrobes;

	void __fastcall Execute();
	void pr(AnsiString _msg);

public:

	__fastcall DataAcquirer(CL10M8PCI_SDK2* _card,RawStrobes* _rawStrobes);
};
#endif
