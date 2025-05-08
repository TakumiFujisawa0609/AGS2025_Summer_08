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
<<<<<<< HEAD

	// カメラ座標をプレイヤー座標と同期させる

	// カメラ設定
	
=======
	// カメラ座標をプレイヤー座標と同期させる

	// カメラ設定
	SetCameraPositionAndAngle(cameraPos_, 0.0f, 0.0f, 0.0f);
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
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
