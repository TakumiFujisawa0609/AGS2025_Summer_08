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
	for (int i = 0; i < 5; i++)
	{
		AimButton* aim = new AimButton(Application::SCREEN_SIZE_X - 300, 250 + (150 * i), 200, 100);

		aim->Init();

		// ¶¬‚µ‚½ƒ{ƒ^ƒ“‚ð”z—ñ‚ÉŠi”[
		aimButtons_.push_back(aim);
	}
}

void AimControl::Update(void)
{
	for (auto buttons : aimButtons_)
	{
		buttons->Update();
	}
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
