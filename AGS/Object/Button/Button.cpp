#include "Button.h"
#include  <DxLib.h>


Button::Button(int posX, int posY, int sizeW, int sizsH)
{
	posX_ = posX;
	posY_ = posY;

	sizeW_ = sizeW;
	sizeH_ = sizsH;

	buttonState_ = BUTTON_STATE::DISABLED;
}

Button::~Button()
{
}

void Button::Init(void)
{
	handle_[DEFOAULT] = LoadGraph("Data/Image/Button/StartButton_0.png");
	handle_[HOVER] = LoadGraph("Data/Image/Button/StartButton_2.png");
	handle_[DISABLED] = LoadGraph("Data/Image/Button/StartButton_1.png");
}

void Button::Update(void)
{
	//マウス座標
	int mousePosX = 0;
	int mousePosY = 0;

	GetMousePoint(&mousePosX, &mousePosY);
	//ボタンの状態
	buttonState_ = DEFOAULT;
	if (posX_ - (sizeW_ / 2) < mousePosX &&//右判定
		posX_ - (sizeW_ / 2) + sizeW_ > mousePosX &&//左判定
		posY_ - (sizeH_ / 2) < mousePosY &&//上判定
		posY_ - (sizeH_ / 2) + sizeH_ > mousePosY)//下判定
	{
		//マウスボタンの上にある状態
		buttonState_ = HOVER;

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//クリックされている
			buttonState_ = DISABLED;
		}
	}
}

void Button::Draw(void)
{
	DrawRotaGraph(posX_, posY_, 1.0f, 0, handle_[buttonState_], true);
}

void Button::Release(void)
{
	for (int i = 0; i < BUTTON_STATE::MAX; i++)
	{
		DeleteGraph(handle_[i]);
	}
}

 Button::BUTTON_STATE Button::GetButtonState(void)
{
	return buttonState_;
}
