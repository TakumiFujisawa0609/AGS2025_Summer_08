#pragma once
#include <DxLib.h>
class Player;

class Camera
{
public:

	// カメラ初期位置
<<<<<<< HEAD
	static constexpr VECTOR INIT_CAMERA_POS = { 0.0f, 0.0f, 0.0f };
	// カメラ初期角度
	static constexpr VECTOR INIT_CAMERA_ANGLE = { 0.0, 0.0f, 0.0f };
=======
	static constexpr VECTOR INIT_CAMERA_POS = { 0.0f, 100.0f, 0.0f };

>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70

	void Init(Player* player);
	void Update(void);
	void Draw(void);
	void Release(void);
	void SetCameraPos(VECTOR cameraPos);
	VECTOR GetCameraPos(void);

private:
	// プレイヤー
	Player* player_;
<<<<<<< HEAD

	// カメラ座標
	VECTOR cameraPos_;
	// カメラ角度
	VECTOR cameraAngle_;
=======

	// カメラ座標
	VECTOR cameraPos_;

};
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70

};