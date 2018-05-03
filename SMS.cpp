//---------------------------------------------------------------------------


#pragma hdrstop

#include "SMS.h"
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Sockets.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <MConnect.hpp>
#include <memory>
#include "Protocol.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
SMS* sms;
//---------------------------------------------------------------------------
SMS::SMS(TComponent *Owner)
{
	Port = 2555;
	ServerName = "Def";//ini->ReadString("SystemConst", "SocketServerName","UranDefect");
	// Security Attributes, Manual Reset , Initial State , Name, UseCOMWait
	client_get = new TEvent(NULL , false , false , "client" , true);

	Server = new TTcpServer(Owner);
	Server->OnAccept = ServerAccept;
	Server->OnCreateHandle = ServerCreateHandle;
	Server->OnDestroyHandle = ServerDestroyHandle;
	Server->OnReceive = (TSocketDataEvent) &ServerReceive;
	Server->OnSend = (TSocketDataEvent) &ServerSend;
	Server->SockType = stStream;
	Server->Name = ServerName;

	Server->LocalPort = Port;
//	Server->Active = true;
	sen_length = 50;

	Client = new TTcpClient(Owner);
	Client->OnSend = (TSocketDataEvent) &ClientSend;
	Client->OnReceive = (TSocketDataEvent) &ClientReceive;
	Client->OnConnect = ClientConnect;
	Client->OnDisconnect = ClientDisconnect;
	Client->OnError = ClientError;
	Client->SockType = stStream;

	Client->RemotePort = Port;
	Client->RemoteHost = ServerName;
}
//---------------------------------------------------------------------------
SMS::~SMS()
{
	Server->Active = false;
	Client->Active = false;
	delete Server;
	delete Client;
}
//---------------------------------------------------------------------------
// �������� ����� ������ � ������
void SMS::SendAnyMessage(String sendString)
{
	std::auto_ptr<TMemoryStream> myStream(new TMemoryStream);
	wchar_t a[100];
	for (int i = 0; i < sendString.Length(); i++)
		a[i] = (sendString[i+1]);

	myStream->Write(a, sendString.Length() * sizeof(wchar_t));
	myStream->Seek(0, 0);
	Client->Active = true;
	Client->SendStream(myStream.get());
	TThread::CurrentThread->Sleep(40);
	Client->ReceiveBuf(client_rec, sen_length ,0);
/*
	String str = "";
	int leng = TcpClient1->BytesReceived / sizeof (wchar_t);
	for (int i=0; i < leng; i++)
		str += (client_rec[i]);

	Memo1->Lines->Add(" Client got data: " + str);
	Memo1->Refresh();
*/
	Client->Active = false;
}
//---------------------------------------------------------------------------
// �������� ����������� ��������� � �������� ���� �� ������
bool SMS::SendZoneThickness(int zone , double thickness)
{
	String str = "zone ";
	str += IntToStr(zone);
	str += " th ";
	str += FloatToStrF(thickness , ffFixed, 3,3);
	SendAnyMessage(str);
	TWaitResult p = client_get->WaitFor(1000);
	if ( p == wrSignaled )
	{
		String rec = client_rec;
		rec = rec.SubString(1, client_rec_length);
		if (rec.SubString(1,7) == "zone ok")
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
// ����������� ����� ����� � �������, ���������� ����� ��� �� �����
int SMS::AskTubeLength()
{
	String str = "length?";
	SendAnyMessage(str);
	TWaitResult p = client_get->WaitFor(1000);
	if ( p == wrSignaled )
	{
		String rec = client_rec;
		rec = rec.SubString(1, client_rec_length);
		if (rec.SubString(1,6) == "length")
		{
			int l = StrToInt(rec.SubString(7, rec.Length()));
			return l;
		}
	}
	return 1;
}
//---------------------------------------------------------------------------
// ���� ����� � ��������, ���������� ���� ���� ����� ����
bool SMS::TestConnection()
{
	String str = "test";
	SendAnyMessage(str);
	TWaitResult p = client_get->WaitFor(1000);
	if ( p == wrSignaled )
	{
		String rec = client_rec;
		rec = rec.SubString(1, client_rec_length);
		if (rec.SubString(1,4) == "test")
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
// ��������� ����� ������� �� ����� ������� �� �������
String SMS::CreateServerRespond()
{
	String rec = server_rec;
	rec = rec.SubString(1, server_rec_length);
	String zone = rec.SubString(1,5);
	if (rec.SubString(1,5) == "zone ")
	{
		int pos = rec.Pos("th");
		int zone = StrToInt(rec.SubString(5, pos - 1 - 5));
		double th = (double) StrToFloat(rec.SubString(pos+2, rec.Length()) );
//		MainForm->th.zones++;
//		MainForm->th.zone_data[ zone ] = th;
//		MainForm->th.PutResultOnChart(MainForm->ThicknessChart , MainForm);
		return "zone ok";
	}
	else if (rec.SubString(1,7) == "length?" )
	{
		String rep = "length ";
//		int zones = MainForm->sum.zones;	//Math::RandomRange(30,60);
//		rep += IntToStr(zones);				// ����� ���
		return rep;
	}
	else if (rec.SubString(1,4) == "test")
	{
    	return "test";
	}
	else
		return "bad";
}

//---------------------------------------------------------------------------
//-------������� �������-----------------------------------------------------
void SMS::StartServer()
{
	Server->Active = true;
}

void __fastcall SMS::ServerAccept(TObject *Sender, TCustomIpClient *ClientSocket)
{
	ClientSocket->ReceiveBuf(server_rec , sen_length , 0);
	server_rec_length = ClientSocket->BytesReceived;
//	Server->ReceiveBuf(server_rec , sen_length , 0);
	int len = Server->BytesReceived ;
	server_rec_length /= sizeof(wchar_t);
	String str = "������ ������� ������: ";
	for (int i = 0; i < server_rec_length; i++)
		str += server_rec[i];
	TPr::pr( str );
	TPr::pr("������ ������� ����: " + IntToStr(len) + ", ����������� ����: " + IntToStr(server_rec_length) );

	// ���������� ������ � ������� �� ������
	String reply = CreateServerRespond();
	TMemoryStream* stream = new TMemoryStream();
	stream->Write(reply.c_str(), reply.Length() * sizeof(wchar_t));
	stream->Seek(0,0);
	ClientSocket->SendStream(stream);

	TPr::pr("������ �������� ������" );
}
void __fastcall SMS::ServerCreateHandle(TObject *Sender)
{
	// ������
	TPr::pr("������ ������");
}
void __fastcall SMS::ServerDestroyHandle(TObject *Sender)
{
	// ������
//	ProtocolForm->SendToProtocol("������ ���������");
}
void __fastcall SMS::ServerSend(TObject *Sender, PChar Buf, int &DataLen)
{
	int len = Server->BytesSent; // / sizeof (int);
	String str = "";
	for (int i = 0; i < DataLen; i++)
		str += (wchar_t) Buf[i];
	TPr::pr(L"������ �������� ������: " + str + L", ����: " + IntToStr(len) );
}
void __fastcall SMS::ServerReceive(TObject *Sender, PChar Buf, int &DataLen)
{
	int len = Server->BytesReceived; // / sizeof (int);
	String str = "";
	for (int i = 0; i < DataLen; i++)
		str += (wchar_t) Buf[i];
	TPr::pr(L"������ ������� ������: " + str + L", ����: " + IntToStr(len) );
}
//---------------------------------------------------------------------------
//-------������� �������-----------------------------------------------------


void __fastcall SMS::ClientSend(TObject *Sender, PChar Buf, int &DataLen)
{
	int len = Client->BytesSent; // / sizeof (int);
	String str = "";
	int reallen = DataLen / sizeof (wchar_t);
	for (int i=0; i < reallen; i++)
		str += (wchar_t)(Buf[i]);
//	ProtocolForm->SendToProtocol(L"������ �������� ������: " + str  );
//	ProtocolForm->SendToProtocol(L"��������: " + IntToStr(reallen) + L", datalen: " + IntToStr(DataLen) );
}
//---------------------------------------------------------------------------
void __fastcall SMS::ClientReceive(TObject *Sender, PChar Buf, int &DataLen)
{
	int len = Client->BytesReceived; // / sizeof (int);
	String str = "";
	client_rec_length = DataLen / sizeof (wchar_t);
	for (int i = 0; i < client_rec_length; i++)
		str += (wchar_t)(Buf[i]);
//	ProtocolForm->SendToProtocol(L"������ ������� ������: " + str );
//	ProtocolForm->SendToProtocol(L"��������: " + IntToStr(client_rec_length) + L", datalen: " + IntToStr(DataLen));
	client_get->SetEvent();
}
//---------------------------------------------------------------------------
void __fastcall SMS::ClientConnect(TObject *Sender)
{
	// ������
//	ProtocolForm->SendToProtocol("������ �����������");
}
void __fastcall SMS::ClientDisconnect(TObject *Sender)
{
	// ������
//	ProtocolForm->SendToProtocol("������ ����������");
}
void __fastcall SMS::ClientError(TObject *Sender, int SocketError)
{
	TPr::pr("������ ����� ������ " + IntToStr(SocketError));
	ShowMessage(L"������ ��� �������� TCP/IP � �������!");
}
