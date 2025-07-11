#include "AimControl.h"
#include "../Button/AimButton.h"
#include "../../Manager/Application.h"

AimControl::AimControl(void)
{
}

AimControl::~AimControl(void)
{
}

void AimControl::Init(void)
{
	int sensi = BUTTON_NUM;

	sensi_ = 1;

	for (int i = 0; i < BUTTON_NUM; i++)
	{
		AimButton* aim = new AimButton(Application::SCREEN_SIZE_X - 300, 250 + (150 * i), 200, 100);

		sensi--;

		aim->Init();
		aim->SetSensi(sensi);

		// 生成したボタンを配列に格納
		aimButtons_.push_back(aim);
	}
}

void AimControl::Update(void)
{
	for (auto buttons : aimButtons_)
	{
		buttons->Update();
	}


	

	// ボタンの検索
	ButtonON();
}

void AimControl::Draw(void)
{
	for (auto buttons : aimButtons_)
	{
		buttons->Draw();
	}
}

void AimControl::Release(void)
{
	for (auto buttons : aimButtons_)
	{
		buttons->Release();
		delete buttons;
	}

	aimButtons_.clear();
}

void AimControl::ButtonON(void)
{
	bool sensiON = false;

	// ボタンを全検索
	for (auto buttons : aimButtons_)
	{
		if (sensiON)
		{
			buttons->ButtonStateOn();
		}

		// 今押されたボタン
		if (buttons->GetNowClick())
		{
			sensi_ = buttons->GetSensi();
			pastSesi = sensi_;
			buttons->ButtonStateOn();
			sensiON = true;
		}
	}
	if (pastSesi == sensi_)
	{
		if (sensi_ == 0)
		{
			controlSensi_ = SENSI_MIN;
		}
		if (sensi_ == 1)
		{
			controlSensi_ = SENSI_ROW;
		}
		if (sensi_ == 2)
		{
			controlSensi_ = SENSI_CENTER;
		}
		if (sensi_ == 3)
		{
			controlSensi_ = SENSI_HIGH;
		}
		if (sensi_ == 4)
		{
			controlSensi_ = SENSI_MAX;
		}
	}

	if (sensiON == true)
	{
		int sensiOff = BUTTON_NUM - sensi_;

		// ボタンを全検索
		for (auto buttons : aimButtons_)
		{
			if (sensiOff == 1)
				break;

			buttons->SetButtonOff();

			sensiOff--;
		}
	}
}

int AimControl::GetButtonSensi(void)
{
	int ret = 10;

	// ボタンを全検索
	for (auto buttons : aimButtons_)
	{
		// 有効なボタンの場所
		if (buttons->GetButtonState() == AimButton::BUTTON_STATE::OFF)
		{
			ret--;
		}
	}

	return ret;
}

