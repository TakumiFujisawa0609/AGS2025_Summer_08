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
}

void Camera::Update(void)
{

	//cameraPos_ = player_->GetPPos();
	
	
	if (CheckHitKey(KEY_INPUT_W)) cameraPos_.y += 20.0f;
	if (CheckHitKey(KEY_INPUT_S)) cameraPos_.y -= 20.0f;
	if (CheckHitKey(KEY_INPUT_A)) cameraPos_.x -= 20.0f;
	if (CheckHitKey(KEY_INPUT_D)) cameraPos_.x += 20.0f;
	if (CheckHitKey(KEY_INPUT_UP)) cameraPos_.z += 20.0f;
	if (CheckHitKey(KEY_INPUT_DOWN)) cameraPos_.z -= 20.0f;

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
