#include <DxLib.h>
#include "Camera.h"
#include "Player.h"
#include "../Manager/Application.h"

void Camera::Init(void)
{
	

	center_X = application_->SCREEN_SIZE_X / 2;
	center_Y = application_->SCREEN_SIZE_Y / 2;

	nowPos_X = application_->SCREEN_SIZE_X / 2;
	nowPos_Y = application_->SCREEN_SIZE_Y / 2;
	
}


void Camera::Update(void)
{
	SetMousePoint(nowPos_X, nowPos_Y);


	// カメラ座標をプレイヤー座標と同期させる
	if (CheckHitKey(KEY_INPUT_A) == true) cameraPos_.x +=  20;
	if (CheckHitKey(KEY_INPUT_D) == true) cameraPos_.x -= 20;



	//ここから
	//マウスの移動制限
	if (nowPos_X > center_X)
	{
		nowPos_X = center_X;
	}

	if (nowPos_Y > center_Y)
	{
		SetMousePoint(center_X, center_Y);
	}
	
	if (center_X > nowPos_X)
	{
		SetMousePoint(center_X, center_Y);
	}
	if (center_Y > nowPos_Y)
	{
		SetMousePoint(center_X, center_Y);
	}
}

void Camera::Draw(void)
{

	DrawFormatString(0, 0, 0xffffff, "cameraPos : (%f, %f, %f)", cameraPos_.x, cameraPos_.y, cameraPos_.z);
	// 座標文字列を描く
	DrawFormatString(0, 100, 0xffffff, "nowPos : %d,%d", nowPos_X, nowPos_Y);

}

void Camera::Release(void)
{
}

void Camera::SetCameraPos(VECTOR cameraPos)
{
	cameraPos_ = cameraPos;
}








