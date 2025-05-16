#include <DxLib.h>
#include "Camera.h"
#include "Player.h"

void Camera::Init(Player* player)
{
	player_ = player;


	// カメラ座標の初期化
	cameraPos_ = INIT_CAMERA_POS;
	// カメラ角度初期化
	cameraAngle_ = INIT_CAMERA_ANGLE;

	// カメラ設定
	SetCameraPositionAndAngle(cameraPos_, cameraAngle_.x, cameraAngle_.y, cameraAngle_.z);
}

void Camera::Update(void)
{
	VECTOR playerPos = player_->GetPPos();
	
	cameraPos_ = playerPos;
	cameraPos_.z -= 500.0f;
	cameraPos_.y += 120.0f;
	
	
	/*if (CheckHitKey(KEY_INPUT_T)) cameraPos_.y += 10.0f;
	if (CheckHitKey(KEY_INPUT_F)) cameraPos_.y -= 10.0f;
	if (CheckHitKey(KEY_INPUT_H)) cameraPos_.x -= 10.0f;
	if (CheckHitKey(KEY_INPUT_G)) cameraPos_.x += 10.0f;
	if (CheckHitKey(KEY_INPUT_UP)) cameraPos_.z += 10.0f;
	if (CheckHitKey(KEY_INPUT_DOWN)) cameraPos_.z -= 10.0f;*/

	float anglesPowRad = 1.0f * DX_PI_F / 180;
	if (CheckHitKey(KEY_INPUT_LEFT)) cameraAngle_.y -= anglesPowRad;
	if (CheckHitKey(KEY_INPUT_RIGHT)) cameraAngle_.y += anglesPowRad;

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
