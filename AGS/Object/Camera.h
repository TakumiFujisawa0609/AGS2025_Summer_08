#pragma once
#include <DxLib.h>
class Player;
class Application;

class Camera
{
public:

	static constexpr int MOVE_CONTROL = 6;
	static constexpr int ANGLE_CONTROL = 1;

	// カメラ初期位置
	static constexpr VECTOR INIT_CAMERA_POS = { 0.0f, 120.0f, -500.0f };

	static constexpr VECTOR INIT_CAMERA_POS = { 0.0f, 0.0f, 1000.0f };

	// カメラ初期角度
	static constexpr VECTOR INIT_CAMERA_ANGLE = { 0.0, 0.0f, 0.0f };

	void Init(void);
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

	int test_X;
	int test_Y;

	int test;

	int testPos;

	//マウス中心固定(ゲームシーン用）
	int center_X;
	int center_Y;
	//マウスの移動先
	int nowPos_X;
	int nowPos_Y;

	int addPos_X;
	int addPos_Y;
};