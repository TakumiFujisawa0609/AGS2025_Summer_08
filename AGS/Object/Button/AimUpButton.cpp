#include "AimUpButton.h"
#include  <DxLib.h>
#include "../../Manager/SoundManager.h"


AimUpButton::AimUpButton(int posX, int posY, int sizeW, int sizsH)
{
	posX_ = posX;
	posY_ = posY;

	sizeW_ = sizeW;
	sizeH_ = sizsH;

	buttonState_ = BUTTON_STATE::DISABLED;

	prevMouseLeftDown_ = false;    // 前フレームの左クリック状態

    counter_ = 0;
}

AimUpButton::~AimUpButton()
{
}

void AimUpButton::Init(void)
{
	handle_[DEFOAULT] = LoadGraph("Data/Image/Button/Up.png");
	handle_[HOVER] = LoadGraph("Data/Image/Button/Up_Hover.png");
	handle_[DISABLED] = LoadGraph("Data/Image/Button/Up.png");
}

void AimUpButton::Update(void)
{
    int mousePosX = 0;
    int mousePosY = 0;
    GetMousePoint(&mousePosX, &mousePosY);

    int mouseInput = GetMouseInput();
    bool isLeftDown = (mouseInput & MOUSE_INPUT_LEFT) != 0;

    // マウスがボタンの上にあるかどうか判定
    bool isMouseOnButton =
        (posX_ - sizeW_ / 2 < mousePosX) &&
        (mousePosX < posX_ + sizeW_ / 2) &&
        (posY_ - sizeH_ / 2 < mousePosY) &&
        (mousePosY < posY_ + sizeH_ / 2);

    // ボタンの見た目（HOVER など）の更新
    if (isMouseOnButton)
    {
        buttonState_ = HOVER;
    }
    else
    {
        buttonState_ = DEFOAULT;
    }

    // エッジ検出：前が押されていなくて、今押されている（押した瞬間）
    if (isMouseOnButton && !prevMouseLeftDown_ && isLeftDown)
    {
        // このタイミングで1回だけ増やす
        counter_++;
        SoundManager::GetInstance()->PlayPause();

        buttonState_ = DISABLED; // 見た目を変えるならここ
    }

    // マウスボタンの状態を次のフレームのために記録
    prevMouseLeftDown_ = isLeftDown;
}


void AimUpButton::Draw(void)
{
	{
		DrawRotaGraph(posX_, posY_, 1.0f, 0, handle_[buttonState_], true);
	}

}

void AimUpButton::Release(void)
{
	for (int i = 0; i < BUTTON_STATE::MAX; i++)
	{
		DeleteGraph(handle_[i]);
	}
}

AimUpButton::BUTTON_STATE AimUpButton::GetButtonState(void)
{
	return buttonState_;
}
