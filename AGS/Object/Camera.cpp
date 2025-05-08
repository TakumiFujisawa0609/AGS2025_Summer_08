#include <DxLib.h>
#include "Camera.h"
#include "Player.h"

void Camera::Init(Player* player)
{
	player_ = player;

	// カメラ座標の初期化
	cameraPos_ = INIT_CAMERA_POS;
	// カメラ初期角度
	cameraAngle_ = INIT_CAMERA_ANGLE;

	// カメラ設定
	SetCameraPositionAndAngle(
		cameraPos_, cameraAngle_.x, cameraAngle_.y, cameraAngle_.z);
}

void Camera::Update(void)
{
	
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
