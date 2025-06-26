#include "Button.h"
#include "../../Manager/SoundManager.h"
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
	handle_[DEFOAULT] = LoadGraph("Data/Image/Button/GameStart.png");
	handle_[HOVER] = LoadGraph("Data/Image/Button/GameStartHover.png");
	handle_[DISABLED] = LoadGraph("Data/Image/Button/GameStart.png");

	//handle_[DEFOAULT] = LoadGraph("Data/Image/Button/Return.png");
	//handle_[HOVER] = LoadGraph("Data/Image/Button/ReturnHover.png");
	//handle_[DISABLED] = LoadGraph("Data/Image/Button/Return.png");
}

void Button::Update(void)
{
	//マウス座標
	int mousePosX = 0;
	int mousePosY = 0;

	GetMousePoint(&mousePosX, &mousePosY);

	// 前フレームの状態を保持する変数を用意（クラスメンバ変数にする必要あり）
	Button::BUTTON_STATE prevButtonState_ = buttonState_;


	//ボタンの状態
	buttonState_ = DEFOAULT;
	if (posX_ - (sizeW_ / 2) < mousePosX &&//右判定
		posX_ - (sizeW_ / 2) + sizeW_ > mousePosX &&//左判定
		posY_ - (sizeH_ / 2) < mousePosY &&//上判定
		posY_ - (sizeH_ / 2) + sizeH_ > mousePosY)//下判定
	{
		// マウスがボタンの上にある
		buttonState_ = HOVER;

		// 前フレームがHOVER以外 → 今フレームHOVER になったタイミングでだけサウンド再生
		if (prevButtonState_ != HOVER)
		{
			SoundManager::GetInstance()->PlayHover();
		}

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			// クリックされている
			buttonState_ = DISABLED;
		}
	}

	// フレームの最後で前回状態を更新
	prevButtonState_ = buttonState_;
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
