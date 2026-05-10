#include "Button.h"

// コンストラクタ
Button::Button(int x, int y, int normalImg, int hoverImg, int pressImg)
    : x(x), y(y),
    normalImg_(normalImg), hoverImg_(hoverImg), pressImg_(pressImg), // 画像を保存
    isHovered_(false), isPressed_(false), prevMouseState_(false)
{
    // 画像からボタンの幅と高さを取得して設定
    GetGraphSize(normalImg_, &width, &height);

    onClick = []() {};
}

// 更新処理
void Button::Update() {

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

	// マウスの左クリック状態
    bool currentMouseState = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
    isHovered_ = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

    if (isHovered_) {
        if (currentMouseState && !prevMouseState_) {
            isPressed_ = true;
        }
        else if (!currentMouseState && prevMouseState_ && isPressed_) {
            onClick(); // コールバック実行
            isPressed_ = false;
        }
    }
    else {
        if (!currentMouseState) {
            isPressed_ = false;
        }
    }
    prevMouseState_ = currentMouseState;
}

// 描画処理
void Button::Draw()
{
    // 通常時の画像をデフォルトに
    int drawImg = normalImg_;

    // 状態を優先度順にチェックして、画像を決定
    if (isPressed_) { // クリック中はクリック画像
        drawImg = pressImg_;
    } 
    else if (isHovered_) { // マウスが乗ってるならホバー画像
        drawImg = hoverImg_;
    }

    // 決定した画像を描画
    DrawGraph(x, y, drawImg, true);
}

// コールバック設定
void Button::SetOnClick(std::function<void()> callback) {
    onClick = callback;
}