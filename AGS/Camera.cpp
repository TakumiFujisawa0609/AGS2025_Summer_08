#include <DxLib.h>
#include "Camera.h"
#include "Player.h"

void Camera::Init(Player* player)
{
	player_ = player;

	// カメラ座標の初期化
	cameraPos_ = INIT_CAMERA_POS;
}

void Camera::Update(void)
{
	// カメラの前方運動量
	cameraPos_.z += CAMERA_MOVE_POWER_Z;
	// カメラX座標をプレイヤーX座標と同期させる
	cameraPos_.x = player_->GetPlayerPos().x;

	// カメラ設定
	SetCameraPositionAndAngle(
		cameraPos_, VECTOR_V, 0.0f, 0.0f);
}

void Camera::Draw(void)
{
}

void Camera::Release(void)
{
}

void Camera::SetCameraPos(VECTOR cameraPos)
{
	cameraPos_ = cameraPos;
}

VECTOR Camera::GetCameraPos(void)
{
	return cameraPos_;
}
