#pragma once
#include <DxLib.h>
class Player;

class Camera
{
public:

	// カメラ初期位置
	static constexpr VECTOR INIT_CAMERA_POS = { 0.0f, 200.0f, -400.f };

	// カメラの前方運動量
	static constexpr float CAMERA_MOVE_POWER_Z = 20.0f;
	// カメラの横軸角度
	static constexpr float VECTOR_V = 0.4f;

	void Init(Player* player);
	void Update(void);
	void Draw(void);
	void Release(void);
	void SetCameraPos(VECTOR cameraPos);
	VECTOR GetCameraPos(void);

private:
	// プレイヤー
	Player* player_;

	// カメラ座標
	VECTOR cameraPos_;

};

