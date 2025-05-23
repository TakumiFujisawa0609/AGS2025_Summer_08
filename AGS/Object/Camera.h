#pragma once
#include <DxLib.h>
class Player;
class Application;

class Camera
{
public:

	//マウス移動量調整
	static constexpr float MOUSE_MOVE_CONTROL = 5;
	//カメラ調整量
	static constexpr float CAMERA_ANGLE_CONTROL = 1;

	static constexpr float ANGLE_DEG = 1.0f;
	static constexpr float MAX_ANGLE_X_RAD = 80.0f * DX_PI_F / 180.0f;
	static constexpr float MIN_ANGLE_X_RAD = -100.0f * DX_PI_F / 180.0f;

	// カメラ初期位置
	static constexpr VECTOR INIT_CAMERA_POS = { 0.0f, 120.0f, -500.0f };

	// カメラ初期角度
	static constexpr VECTOR INIT_CAMERA_ANGLE = { 0.0, 0.0f, 0.0f };

	void Init(Player* player);
	void Update(void);
	void Draw(void);
	void Release(void);
	void SetCameraPos(VECTOR cameraPos);

	void MouseLmit(void);
	void AddAngle(void);


private:
	// プレイヤー
	Player* player_;
	Application* application_;
	// カメラ座標
	VECTOR cameraPos_;
	// カメラ角度
	VECTOR cameraAngle_;

	VECTOR angle_;
	int test_X;
	int test_Y;

	int test;

	int prevPos_X;
	int prevPos_Y;
	//マウス中心固定(ゲームシーン用）
	//int center_X;
	//int center_Y;
	//マウスの移動先
	int nowPos_X;
	int nowPos_Y;

	/*int prevPos_X;
	int prevPos_Y;*/

	//マウスの現在の位置
	int mousePow_X;
	int mousePow_Y;

	int rad;
	//カメラ移動量
	int cameraPow_X;
	int cameraPow_Y;


};