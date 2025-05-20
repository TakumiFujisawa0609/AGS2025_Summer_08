#include <DxLib.h>
#include "Camera.h"
#include "Player.h"
#include "../Manager/Application.h"

void Camera::Init(void)
{
	


	// カメラ座標の初期化
	cameraPos_ = INIT_CAMERA_POS;
	// カメラ角度初期化
	cameraAngle_ = INIT_CAMERA_ANGLE;

	// カメラ設定
	SetCameraPositionAndAngle(cameraPos_, cameraAngle_.x, cameraAngle_.y, cameraAngle_.z);

	//center_X = application_->SCREEN_SIZE_X / 2;
	//center_Y = application_->SCREEN_SIZE_Y / 2;

	//初期位置
	nowPos_X = application_->SCREEN_SIZE_X / 2;
	nowPos_Y = application_->SCREEN_SIZE_Y / 2;

	cameraAngle_ = VGet(0.0f, 0.0f, 0.0f);

	SetMousePoint(center_X, center_Y);

	test = 0;
	
	

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

	MouseLmit();
	AddAngle();


	
	if (nowPos_X >= testPos)
	{
		test += 1;
		testPos -= testPos;
	}

	GetMousePoint(&nowPos_X, &nowPos_Y);

	testPos = nowPos_X + MOVE_CONTROL;



	// カメラ座標をプレイヤー座標と同期させる
	if (CheckHitKey(KEY_INPUT_A) == true) cameraPos_.x +=  20;
	if (CheckHitKey(KEY_INPUT_D) == true) cameraPos_.x -= 20;


	
}

void Camera::Draw(void)
{


	SetCameraPositionAndAngle(cameraPos_, cameraAngle_.x, cameraAngle_.y, cameraAngle_.z);

	DrawFormatString(0, 50, 0xffffff, "Angle : (%f, %f, %f)", cameraAngle_.x, cameraAngle_.y, cameraAngle_.z);
	DrawFormatString(0, 0, 0xffffff, "cameraPos : (%f, %f, %f)", cameraPos_.x, cameraPos_.y, cameraPos_.z);
	// 座標文字列を描く
	DrawFormatString(0, 100, 0xffffff, "nowPos : %d,%d", nowPos_X, nowPos_Y);



	DrawFormatString(0, 200, 0xffffff, "test : %d", test);



}

void Camera::Release(void)
{
}

void Camera::SetCameraPos(VECTOR cameraPos)
{
	cameraPos_ = cameraPos;

}



void Camera::MouseLmit(void)
{

	//マウスの移動制限
	if (nowPos_X >= application_->SCREEN_SIZE_X)
	{
		nowPos_X = nowPos_X - 10;
	}
	if (nowPos_X <= 0)
	{
		nowPos_X = nowPos_X + 10;
	}

	if (nowPos_Y >= application_->SCREEN_SIZE_Y)
	{
		nowPos_Y = nowPos_Y - 10;
	}
	if (nowPos_Y <= 0)
	{
		nowPos_Y = nowPos_Y + 10;
	}
}

void Camera::AddAngle(void)
{
	//X軸の視点移動
	if (nowPos_X >= (nowPos_X + MOVE_CONTROL))
	{
		cameraAngle_.x =  cameraAngle_.x + ANGLE_CONTROL;
	}
	if (nowPos_X <= nowPos_X - MOVE_CONTROL)
	{
		cameraAngle_.x -= ANGLE_CONTROL;
	}

	//Y軸の視点移動
	if (nowPos_Y >= nowPos_Y + MOVE_CONTROL)
	{
		cameraAngle_.y += ANGLE_CONTROL;
	}
	if (nowPos_Y <= nowPos_Y - MOVE_CONTROL)
	{
		cameraAngle_.y -= ANGLE_CONTROL;
	}
}








