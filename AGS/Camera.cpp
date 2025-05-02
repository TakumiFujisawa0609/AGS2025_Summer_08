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
	// カメラ座標をプレイヤー座標と同期させる
	

	// カメラ設定
	SetCameraPositionAndAngle(
		cameraPos_, 0.4f, 0.0f, 0.0f);
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
