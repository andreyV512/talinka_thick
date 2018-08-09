// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

// using Microsoft::ManagementConsole::Advanced;

#include "Manage.h"
#include "Global.h"
#include "uFunctions.h"
#include "Protocol.h"
//#include "LCARD502.h"
#include "A1730.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TManageForm *ManageForm;

// ---------------------------------------------------------------------------
__fastcall TManageForm::TManageForm(TComponent* Owner, TIniFile* _ini)
	: TForm(Owner)
{
	ini = _ini;
	// задаем имена для кнопок и состояний, картинки и цвета
	centr_on = "Сжат";
	centr_off = "Разжат";
	centr_close = "Сжать";
	centr_open = "Разжать";
	centr_cl = new Graphics::TBitmap();
	centr_op = new Graphics::TBitmap();

	KeyPreview = true;

	mod_on = "В работе";
	mod_off = "Обслуживание";
	mod_mov = "Перемещается";
	mod_work = "Включить";
	mod_service = "Отключить";
	mod_dsbl = "Недоступно";
	mod_serv = new Graphics::TBitmap();
	mod_wrk = new Graphics::TBitmap();
	mod_mvg = new Graphics::TBitmap();
	try
	{
		mod_serv->LoadFromFile("..\\..\\Pix\\Module-Service.bmp");
		mod_wrk->LoadFromFile("..\\..\\Pix\\Module-Work.bmp");
		mod_mvg->LoadFromFile("..\\..\\Pix\\Module-Move.bmp");
		centr_cl->LoadFromFile("..\\..\\Pix\\Centralizer-close.bmp");
		centr_op->LoadFromFile("..\\..\\Pix\\Centralizer-open.bmp");
		is_pix_ok = true;
	}
	catch (...)
	{
		is_pix_ok = false;
		Application->MessageBoxW
			(L"Изображения для динамических кнопок не найдены. \n Ошибка 500",
			L"Ошибка", MB_ICONERROR);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TManageForm::FormShow(TObject *Sender)
{
	// читаем цвета из файла
	on = (TColor)ini->ReadInteger("Color", "ActiveIn", 0);
	off = (TColor)ini->ReadInteger("Color", "NotActiveIn", 0);
	move = (TColor)ini->ReadInteger("Color", "NotActiveOut", 0);
	int speed = frConverter->getParameterSpeed(Globals_defaultRotParameter);
	cbRL->Checked = 0 != (speed & 1);
	cbRM->Checked = 0 != (speed & 2);
	cbRH->Checked = 0 != (speed & 4);
	// включаем таймер, отслеживающий состояние входов и выходов
	butt_enabled = true;
	StatusBarBottom->Panels->Items[0]->Text = "";
	StatusBarBottom->Refresh();
}

// ---------------------------------------------------------------------------
void __fastcall TManageForm::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 27)
		Close();
}

// ---------------------------------------------------------------------------
void TManageForm::ShowCentralizerOpened(TBitBtn *btn, TPanel *pan)
{
	// схват разжат, задаем соответствующие параметры объектам, связанным с ним
	pan->Color = off;
	pan->Caption = centr_off;
	btn->Caption = centr_close;
	btn->Glyph = centr_cl;
}
// ---------------------------------------------------------------------------

void TManageForm::ShowCentralizerClosed(TBitBtn *btn, TPanel *pan)
{
	// схват сжат, задаем соответствующие параметры объектам, связанным с ним
	pan->Color = on;
	pan->Caption = centr_on;
	btn->Caption = centr_open;
	btn->Glyph = centr_op;
}

// ---------------------------------------------------------------------------
void TManageForm::ShowModuleinWork(TBitBtn *btn, TPanel *pan)
{
	// модуль в работе , задаем соответствующие параметры объектам, связанным с ним
	pan->Color = on;
	pan->Caption = mod_on;
	btn->Caption = mod_service;
	btn->Glyph = mod_serv;

	if (butt_enabled)
		btn->Enabled = true;
	else
		btn->Enabled = false;
}

// ---------------------------------------------------------------------------
void TManageForm::ShowModuleinService(TBitBtn *btn, TPanel *pan)
{
	// модуль в положении обслуживания , задаем соответствующие параметры объектам, связанным с ним
	pan->Color = off;
	pan->Caption = mod_off;
	btn->Caption = mod_work;
	btn->Glyph = mod_wrk;

	if (butt_enabled)
		btn->Enabled = true;
	else
		btn->Enabled = false;
}
// ---------------------------------------------------------------------------

void TManageForm::ShowModuleMoving(TBitBtn *btn, TPanel *pan)
{
	// модуль перемещается из одного положения в другое , задаем соответствующие параметры объектам, связанным с ним
	pan->Color = move;
	pan->Caption = mod_mov;
	btn->Enabled = false;
	btn->Caption = mod_dsbl;
	btn->Glyph = mod_mvg;
}

// ---------------------------------------------------------------------------
void TManageForm::ShowModuleState(byte state, TBitBtn *btn, TPanel *pan)
{
	switch (state)
	{
	case 0:
		ShowModuleMoving(btn, pan);
		break;
	case 1:
		ShowModuleinWork(btn, pan);
		break;
	case 2:
		ShowModuleinService(btn, pan);
		break;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TManageForm::FormDestroy(TObject *Sender)
{
	delete centr_cl;
	delete centr_op;
	delete mod_serv;
	delete mod_wrk;
	delete mod_mvg;
	SaveFormPos(this, ini);
}
// ---------------------------------------------------------------------------

void __fastcall TManageForm::bRotationClick(TObject *Sender)
{
	if (bRotation->Caption == "Вращать")
	{
	/*
		if(!a1730->oPCHPOW->Get())
		{
			a1730->oPCHPOW->Set(true);
			Sleep(1000);
		}
		*/
		int speed = 0;
		if(cbRL->Checked) speed |= 1;
		if(cbRM->Checked) speed |= 2;
		if(cbRH->Checked) speed |= 4;
		if (!frConverter->setParameterSpeed(Globals_defaultRotParameter, speed))
		{
			TPr::pr("frConverter->setParameterSpeed false");
			StatusBarBottom->Panels->Items[0]->Text =
				"Не удалось выставить скорость вращения";
			StatusBarBottom->Refresh();
			return;
		}
		else
		{
			StatusBarBottom->Panels->Items[0]->Text = "";
			StatusBarBottom->Refresh();
        }
		if (!frConverter->startRotation())
		{
			TPr::pr("frConverter->startRotation false");
			StatusBarBottom->Panels->Items[0]->Text =
				"Не удалось включить вращение";
			StatusBarBottom->Refresh();
			return;
		}
		else
		{
            StatusBarBottom->Panels->Items[0]->Text = "";
			StatusBarBottom->Refresh();
        }
		DWORD startTick = GetTickCount();
		bool started = false;
		for (; ;)
		{
			if (a1730->iPCHRUN->Get())
			{
				started = true;
				break;
			}
			if (GetTickCount() > startTick + 4000)
				break;
		}
		if (!started)
		{
			TPr::pr("Не дождались iPCHRUN за 4 секn.");
			StatusBarBottom->Panels->Items[0]->Text =
				"Не удалось выставить скорость вращения";
			StatusBarBottom->Refresh();
			return;
		}
		bRotation->Caption = "Остановить";
	}
	else
	{
		if (!frConverter->stopRotation())
		{
			TPr::pr("frConverter->stopRotation() false");
			StatusBarBottom->Panels->Items[0]->Text =
				"Не удалось остановить ПЧ";
			StatusBarBottom->Refresh();
			return;
		}
		DWORD startTick = GetTickCount();
		bool stoped = false;
		for (; ;)
		{
			if (!a1730->iPCHRUN->Get())
			{
				stoped = true;
				break;
			}
			if (GetTickCount() > startTick + 2000)
				break;
		}
		if (!stoped)
		{
			TPr::pr("Не дождались снятия iPCHRUN за 2 сек.");
			StatusBarBottom->Panels->Items[0]->Text =
				"Не удалось остановить вращение";
			StatusBarBottom->Refresh();
			return;
		}
		bRotation->Caption = "Вращать";
	}
}
// ---------------------------------------------------------------------------


void __fastcall TManageForm::FormCreate(TObject * Sender)
{
	LoadFormPos(this, ini);
}
// ---------------------------------------------------------------------------

