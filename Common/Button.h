#pragma once
#include <string>
#include <functional>
#include <DxLib.h>

class Button
{
public:

	// コンストラクタ
	Button(int x, int y, int normalImg, int hoverImg, int pressImg);

	// 更新処理
	void Update();
	// 描画処理
	void Draw();

	// コールバック関数の登録
	void SetOnClick(std::function<void()> callback);

private:

	// ボタンの位置とサイズ
	int x, y, width, height;

	// 画像ハンドル
	int normalImg_;	// 通常時
	int hoverImg_;  // ホバー時
	int pressImg_; // クリック時

	// 状態管理
	bool isHovered_;
	bool isPressed_;
	bool prevMouseState_; // 前フレームのクリック状態

	// コールバック関数
	std::function<void()> onClick;
};