#pragma once
#include <string>
#include <functional>
#include <DxLib.h>

class Button
{
public:

	// コンストラクタ
	Button(int x, int y, int width, int height);

	// 更新処理
	void Update();
	// 描画処理
	void Draw();

	// コールバック関数の登録
	void SetOnClick(std::function<void()> callback);

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