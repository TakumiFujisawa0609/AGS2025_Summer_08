#include <DxLib.h>
#include "Camera.h"
#include "Player.h"
#include "../Manager/Application.h"
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"

void Camera::Init(Player* player)
{
	player_ = player;	// ゲームシーン内のプレイヤーポインタを取得

	// 画面の中央を設定
	centerX_ = Application::SCREEN_SIZE_X / 2;
	centerY_ = Application::SCREEN_SIZE_Y / 2;

	//水平・垂直の角度初期化
	yaw_ = 0.0f;
	pitch_ = 0.0f;
	
	// カメラの初期位置
	pos_ = { 0.0f, 0.0f, 0.0f };

	// ゲーム内フラグ
	isInGame_ = true;

	if (isInGame_)SetMouseDispFlag(false);
	if (!isInGame_)SetMouseDispFlag(true);

	SetMousePoint(centerX_, centerY_);	// マウスセット
	GetMousePoint(&prevPosX_, &prevPosY_);	// マウスの位置取得

	// 追従対象からのローカル座標設定
	localPosFrom_ = { 0.0f, HEIGHT, -DIS_FOLLOW_TO_CAMERA };
	// 追従対象からのローカル座標の回転値
	localRotFrom_ = { 0.0f, 0.0f, 0.0f };


}


void Camera::Update(void)
{
	// マウス座標取得
	GetMousePoint(&movedPosX_, &movedPosY_);

	if (!isInGame_) {
		//移動制限
		MouseLimit();
	}

	if (isInGame_) {
		// アングル処理（マウスの動き量からYaw/Pitchを計算）
		Angle();
	}

	// マウスを中央に戻す
	SetMousePoint(centerX_, centerY_);
}

void Camera::Draw(void)
{

}

void Camera::Release(void)
{
}

void Camera::MouseLimit(void)
{
	//マウスの移動制限
	int limit = 15;
	//マウスの移動制限
	if (movedPosX_ >= Application::SCREEN_SIZE_X - limit)
	{
		movedPosX_ = Application::SCREEN_SIZE_X - limit;
	}
	if (movedPosX_ <= 0)
	{
		movedPosX_ = limit ;
	}

	if (movedPosY_ >= Application::SCREEN_SIZE_Y)
	{
		movedPosY_ = Application::SCREEN_SIZE_Y - limit;
	}
	if (movedPosY_ <= 0)
	{
		movedPosY_ = limit;
	}
	SetMousePoint(movedPosX_, movedPosY_);
}

// アングル処理
void Camera::Angle(void)
{
	// 前のマウス位置との差分
	int deltaX = movedPosX_ - centerX_;
	int deltaY = movedPosY_ - centerY_;

	// 角度更新（感度調整）
	const float sensitivity = 0.002f; // センシ調整
	// 更新
	yaw_ += deltaX * sensitivity;
	pitch_ += deltaY * sensitivity;

	// ピッチ制限（上向きすぎ・下向きすぎを防ぐ）
	const float limit = DX_PI_F / 2.5f; // 72度ぐらい
	if (pitch_ > limit) pitch_ = limit;
	if (pitch_ < -limit) pitch_ = -limit;

	// 追従対象の位置（Yaw/Pitchに基づく）
	VECTOR followPos = player_->GetPPos();
	// プレイヤーの目線位置をカメラの位置とする
	pos_ = VGet(followPos.x, followPos.y + HEIGHT, followPos.z);

	// 前方向ベクトルを計算
	forward_ = {
		cosf(pitch_) * sinf(yaw_),
		sinf(pitch_),
		cosf(pitch_) * cosf(yaw_)
	};
	
	// カメラの位置を前方向にする
	pos_ = VAdd(pos_, forward_);


	// カメラセット
	SetCameraPositionAndTargetAndUpVec(
		pos_,
		VGet(followPos.x, followPos.y + HEIGHT, followPos.z),
		VGet(0, 1, 0)
	);

	// 更新した回転角度はlocalRotFrom_に格納しておく（必要なら）
	localRotFrom_.x = pitch_;
	localRotFrom_.y = yaw_;
	localRotFrom_.z = 0.0f;

}

// 前方向取得
VECTOR Camera::GetForward() const
{
	return forward_;
}

// 座標取得
VECTOR Camera::GetPos() const
{
	return pos_;
}








