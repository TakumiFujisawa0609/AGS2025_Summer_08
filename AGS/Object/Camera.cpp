#include <DxLib.h>
#include "Camera.h"
#include "Player.h"
#include "../Manager/Application.h"
#include "../Utility/AsoUtility.h"

void Camera::Init(Player* player)
{
	player_ = player;	// ゲームシーン内のプレイヤーポインタを取得
	// カメラ座標の初期化
	//cameraPos_ = VGet(player_->GetPPos().x, player_->GetPPos().y + 50, player_->GetPPos().z);
	// カメラ角度初期化
	cameraAngle_ = INIT_CAMERA_ANGLE;
	//マウスの初期位置設定
	//SetMousePoint(center_X, center_Y);
	//カメラアングル初期設定
	angle_ = VGet(0.0f, 0.0f, 0.0f);

	// カメラ設定
	SetCameraPositionAndAngle(cameraPos_, angle_.x, angle_.y, angle_.z);

	//center_X = application_->SCREEN_SIZE_X / 2;
	//center_Y = application_->SCREEN_SIZE_Y / 2;


	//マウス初期位置
	test = 0;
	
}


void Camera::Update(void)
{

	// カメラ設定
	SetCameraPositionAndAngle(cameraPos_, angle_.x, angle_.y, angle_.z);

	VECTOR playerPos = player_->GetPPos();
	//cameraPos_ = VGet(playerPos.x, playerPos.y + 100, playerPos.z - 20);
	cameraPos_ = VGet(playerPos.x, playerPos.y + 300, playerPos.z - 420);


	prevPos_X = nowPos_X;
	prevPos_Y = nowPos_Y;
	GetMousePoint(&nowPos_X, &nowPos_Y);
	mousePow_X = nowPos_X - prevPos_X;
	mousePow_Y = nowPos_Y - prevPos_Y;
	
	//デバッグ
	float anglesPowRad = 1.0f * DX_PI_F / 180;
	if (CheckHitKey(KEY_INPUT_LEFT)) cameraAngle_.y -= anglesPowRad;
	if (CheckHitKey(KEY_INPUT_RIGHT)) cameraAngle_.y += anglesPowRad;

	// 安藤作業中↓
	MouseLimit();
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

	if (angle_.y >= 360.0f)
	{
		angle_.y = 0.0f;
	}
	
}

void Camera::Draw(void)
{

	DrawFormatString(0, 60, 0xffffff, "Angle : (%f, %f, %f)", angle_.x, angle_.y, angle_.z);
	DrawFormatString(0, 0, 0xffffff, "cameraPos : (%f, %f, %f)", cameraPos_.x, cameraPos_.y, cameraPos_.z);
	// 座標文字列を描く
	DrawFormatString(0, 100, 0xffffff, "nowPos : %d,%d", nowPos_X, nowPos_Y);
	DrawFormatString(0, 200, 0xffffff, "mousePow_X : %d", mousePow_X);
	DrawFormatString(0, 150, 0xffffff, "cameraPow_X : %d", cameraPow_X);

}

void Camera::Release(void)
{
}

void Camera::SetCameraPos(VECTOR cameraPos)
{
	cameraPos_ = cameraPos;

}



void Camera::MouseLimit(void)
{
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

	int lowPow = 1;
	rad = ANGLE_DEG * DX_PI_F / 180;

	//mousePow_X = nowPos_X - prevPos_X;
	//mousePow_Y = nowPos_Y - prevPos_Y;


	//マウスでplayerの視点移動
	if (abs(mousePow_X) > lowPow)
	{
		cameraPow_X = mousePow_X / MOUSE_MOVE_CONTROL;
		angle_.y += AsoUtility::Deg2RadF(cameraPow_X);
	
	}

	if (abs(mousePow_Y) > lowPow)
	{
		cameraPow_Y = mousePow_Y / MOUSE_MOVE_CONTROL;
		angle_.x += AsoUtility::Deg2RadF(cameraPow_Y);
		if (angle_.x > MAX_ANGLE_X_RAD)
		{
			angle_.x = MAX_ANGLE_X_RAD;
		}
		if (angle_.x < MIN_ANGLE_X_RAD)
		{
			angle_.x = MIN_ANGLE_X_RAD;
		}
	}



	//if (mousePow_X < lowPow)
	//{
	//	//angle_.y = rad - (mousePow_X / MOUSE_MOVE_CONTROL);

	//
	//	cameraPow_X = mousePow_X / MOUSE_MOVE_CONTROL;
	//	angle_.y -= AsoUtility::Deg2RadF(cameraPow_X);

	//}
}








