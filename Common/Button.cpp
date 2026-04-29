#include "Button.h"

// コンストラクタ
Button::Button(int x, int y, int w, int h)
    : x(x), y(y), width(w), height(h),
    isHovered(false), isPressed(false), prevMouseState(false)
{
    onClick = []() {};
}

// 更新処理
void Button::Update() {
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

	// マウスの左クリック状態
    bool currentMouseState = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
    isHovered = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

    if (isHovered) {
        if (currentMouseState && !prevMouseState) {
            isPressed = true;
        }
        else if (!currentMouseState && prevMouseState && isPressed) {
            onClick();
            isPressed = false;
        }
    }
    else {
        if (!currentMouseState) {
            isPressed = false;
        }
    }
    prevMouseState = currentMouseState;
}

// 描画処理
void Button::Draw()
{

}

// コールバック設定
void Button::SetOnClick(std::function<void()> callback) {
    onClick = callback;
}