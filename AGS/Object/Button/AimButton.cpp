#include <DxLib.h>
#include "AimButton.h"
#include "../../Manager/InputManager.h"

AimButton::AimButton(int posX, int posY, int sizeW, int sizsH)
{
	posX_ = posX;
	posY_ = posY;

	sizeW_ = sizeW;
	sizeH_ = sizsH;

	buttonState_ = BUTTON_STATE::OFF;
}

AimButton::~AimButton()
{
}

void AimButton::Init(void)
{
	handle_[OFF] = LoadGraph("Data/Image/Button/AimButton_Off.png");
	handle_[ON] = LoadGraph("Data/Image/Button/AimButton_On.png");//今回はHOVERがボタンが押された状態
	
	 prevMouseDown_ = false;
	 nowClick_ = false;

}

void AimButton::Update(void)
{
	// マウス座標取得
	nowClick_ = false;
	int mousePosX = 0, mousePosY = 0;
	GetMousePoint(&mousePosX, &mousePosY);

	// マウスがボタン上にあるかチェック
	bool mouseOnButton =
		posX_ - (sizeW_ / 2) < mousePosX &&
		mousePosX < posX_ - (sizeW_ / 2) + sizeW_ &&
		posY_ - (sizeH_ / 2) < mousePosY &&
		mousePosY < posY_ - (sizeH_ / 2) + sizeH_;

	// マウス左クリック取得
	bool mouseDown = InputManager::GetInstance().IsTrgMouseLeft();

	// マウスがボタン上で、クリックされた時
	if (mouseOnButton && mouseDown && !prevMouseDown_) {
		// 状態トグル
		if (buttonState_ == OFF) {
			buttonState_ = ON;
			nowClick_ = true;
		}
		else if (buttonState_ == ON) {
			buttonState_ = OFF;
			nowClick_ = true;
		}
	}

	// 次フレーム用に保存
	prevMouseDown_ = mouseDown;
}


void AimButton::Draw(void)
{
	DrawRotaGraph(posX_, posY_, 1.0f, 0, handle_[buttonState_], true);
}

void AimButton::Release(void)
{
	for (int i = 0; i < BUTTON_STATE::MAX; i++)
	{
		DeleteGraph(handle_[i]);
	}
}

AimButton::BUTTON_STATE AimButton::GetButtonState(void)
{
	return buttonState_;

}

void AimButton::ButtonStateOn(void)
{
	buttonState_ = BUTTON_STATE::ON;
}

