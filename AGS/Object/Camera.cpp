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
	SetCameraPositionAndAngle(cameraPos_, cameraAngle_.x, cameraAngle_.y, cameraAngle_.z);
}

void Camera::Draw(void)
{
	DrawFormatString(0, 0, 0xffffff, "cameraPos : (%f, %f, %f)", cameraPos_.x, cameraPos_.y, cameraPos_.z);
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
