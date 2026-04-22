#pragma once
#include <string>
#include <functional>

class Button
{
public:

	// コンストラクタ
	Button(int x, int y, int width, int height);

	// コールバック関数の登録
	void SetOnClick(std::function<void()> callback);

	// 更新処理
	void Update();
	// 描画処理
	void Draw();

private:

	// ボタンサイズ
	int x, y, width, height;

	// 状態管理
	bool isHovered;
	bool isPressed;
	bool prevMouseState; // 前フレームのクリック状態

	// コールバック関数
	std::function<void()> onClick;
};