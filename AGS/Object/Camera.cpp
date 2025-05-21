#include <DxLib.h>
#include "Camera.h"
#include "Player.h"
#include "../Manager/Application.h"
#include "../Utility/AsoUtility.h"

void Camera::Init(Player* player)
{
	player_ = player;	// ゲームシーン内のプレイヤーポインタを取得

	// カメラ座標の初期化
	cameraPos_ = INIT_CAMERA_POS;
	// カメラ角度初期化
	cameraAngle_ = INIT_CAMERA_ANGLE;

	angle_X = 0.0f;
	angle_Y = 0.0f;
	angle_Z = 0.0f;

	//初期位置
	nowPos_X = application_->SCREEN_SIZE_X / 2;
	nowPos_Y = application_->SCREEN_SIZE_Y / 2;

	//マウス初期位置
	SetMousePoint(center_X, center_Y);
	// カメラ設定
	SetCameraPositionAndAngle(cameraPos_, angle_X, angle_Y, angle_Z);
	test = 0;
	
}


void Camera::Update(void)
{
	// カメラ設定
	SetCameraPositionAndAngle(cameraPos_, angle_X, angle_Y, angle_Z);

	VECTOR playerPos = player_->GetPPos();
	
	GetMousePoint(&nowPos_X, &nowPos_Y);

	cameraPos_ = playerPos;
	cameraPos_.z -= 500.0f;
	cameraPos_.y += 120.0f;
	
	if (CheckHitKey(KEY_INPUT_UP)) cameraPos_.z += 10.0f;
	if (CheckHitKey(KEY_INPUT_DOWN)) cameraPos_.z -= 10.0f;

	float anglesPowRad = 1.0f * DX_PI_F / 180;
	if (CheckHitKey(KEY_INPUT_LEFT)) cameraAngle_.y -= anglesPowRad;
	if (CheckHitKey(KEY_INPUT_RIGHT)) cameraAngle_.y += anglesPowRad;

	// 安藤作業中↓
	MouseLmit();
	AddAngle();
	


	if (nowPos_X > test_X)
	{
		test += 1;
		test_X = nowPos_X;
	}
	else if (nowPos_X < test_X)
	{
		test += 1;
		test_X = nowPos_X ;
	}
	

	if (nowPos_Y > test_Y)
	{
		test += 1;
		test_Y = nowPos_Y ;
	}
	else if (nowPos_Y < test_Y)
	{
		test += 1;
		test_Y = nowPos_Y ;
	}
	

	//---------------------------------------↑

	
	
}

void Camera::Draw(void)
{

	DrawFormatString(0, 60, 0xffffff, "Angle : (%f, %f, %f)", angle_X, angle_Y, angle_Z);
	DrawFormatString(0, 0, 0xffffff, "cameraPos : (%f, %f, %f)", cameraPos_.x, cameraPos_.y, cameraPos_.z);
	// 座標文字列を描く
	DrawFormatString(0, 100, 0xffffff, "nowPos : %d,%d", nowPos_X, nowPos_Y);

	DrawFormatString(0, 200, 0xffffff, "test : %d", test);

	DrawFormatString(0, 150, 0xffffff, "testPos : %d ,%d", test_X,test_Y);

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
	mousePow_X = nowPos_X - center_X;
	mousePow_Y = nowPos_Y - center_Y;


	//マウスの移動制限
	int limit = 10;
	//マウスの移動制限
	if (nowPos_X >= application_->SCREEN_SIZE_X - limit)
	{
		nowPos_X = application_->SCREEN_SIZE_X - limit;
	}
	if (nowPos_X <= 0)
	{
		nowPos_X = limit ;
	}

	if (nowPos_Y >= application_->SCREEN_SIZE_Y)
	{
		nowPos_Y = application_->SCREEN_SIZE_Y - limit;
	}
	if (nowPos_Y <= 0)
	{
		nowPos_Y = limit;
	}

	SetMousePoint(nowPos_X, nowPos_Y);
}

void Camera::AddAngle(void)
{
	int lowPow = 0;

	if (mousePow_X > lowPow)
	{
		cameraPow_X = mousePow_X / MOVE_CONTROL;
		angle_X = AsoUtility::Deg2RadF(cameraPow_X);
	}
	angle_X += AsoUtility::Deg2RadF(mousePow_X);
	
}








