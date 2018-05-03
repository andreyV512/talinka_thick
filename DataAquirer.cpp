// ---------------------------------------------------------------------------
#pragma hdrstop
#include "DataAquirer.h"
#include "Protocol.h"
#pragma package(smart_init)
#include "A1730.h"

// ---------------------------------------------------------------------------
__fastcall DataAcquirer::DataAcquirer( CL10M8PCI_SDK2* _card, RawStrobes* _rawStrobes
	) : TThread(false)
{
	rawStrobes = _rawStrobes;
	card = _card;
	FreeOnTerminate = false;
}

// ---------------------------------------------------------------------------
void __fastcall DataAcquirer::Execute()
{
	AnsiString a="DataAcquirer::Execute: ������: ������ ������: ";
	a+=card->GetBufSize();
	pr(a);
	char* data=new char[card->GetBufSize()];
	for (; ;)
	{
		if (card->Read(data))
			rawStrobes->Add(data,GetTickCount());
		else
		{
			pr("DataAcquirer::Execute: ������ ������ ������");
			a1730->Latchterminate("������ ������ ������");
			a1730->SetLatchError();
			break;
		}
		if (Terminated)
			break;
	}
	delete data;
	pr("DataAcquirer::Execute: ���������");
}

void DataAcquirer::pr(AnsiString _msg)
{
	TPr::pr(_msg);
}


