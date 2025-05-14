#pragma once
#include <DxLib.h>
class Player;
class Application;

class Camera
{
public:

	// カメラ初期位置
	static constexpr VECTOR INIT_CAMERA_POS = { 0.0f, 0.0f, 1000.0f };
	// カメラ初期角度
	static constexpr VECTOR INIT_CAMERA_ANGLE = { 0.0, 0.0f, 0.0f };

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	void SetCameraPos(VECTOR cameraPos);


private:
	// プレイヤー
	Player* player_;
	Application* application_;
	// カメラ座標
	VECTOR cameraPos_;
	// カメラ角度
	VECTOR cameraAngle_;




	//マウス中心固定(ゲームシーン用）
	int center_X;
	int center_Y;
	//マウスの移動先
	int nowPos_X;
	int nowPos_Y;
};