#pragma once
#include <DxLib.h>
class Player;

class Camera
{
public:

	// カメラ初期位置
	static constexpr VECTOR INIT_CAMERA_POS = { 0.0f, 100.0f, 0.0f };


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

