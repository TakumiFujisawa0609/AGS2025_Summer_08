#pragma once
#include <DxLib.h>
class Player;
class Application;
class AimControl;

class Camera
{
public:

	// カメラの高さ
	static constexpr float HEIGHT = 150.0f;

	// 追従対象からカメラまでの距離
	static constexpr float DIS_FOLLOW_TO_CAMERA = 500.0f;

	// 回転スピード
	static constexpr float ROT_SPEED_DEG = 1.0f;


	void Init(Player* player);
	void Update(void);
	void Draw(void);
	void Release(void);

	void MouseLimit(void);
	void Angle(void);

	// カメラ回転角度の取得
	VECTOR GetAngles(void) { return localRotFrom_; }

	// 前方向取得
	VECTOR GetForward() const;
	// カメラ座標取得
	VECTOR GetPos() const;

	void UpdateDeathCamera();
	float GetcontrolSensi_(void) { return controlSensi_; }
	void  SetcontrolSensi_(float controlSensi) { controlSensi_ = controlSensi; }

private:
	// プレイヤー
	Player* player_;
	//エイムコントロール
	AimControl* aimControl_;

	// 前のマウス位置
	int prevPosX_;
	int prevPosY_;
	//マウスの移動先
	int movedPosX_;
	int movedPosY_;

	////マウス中心固定(ゲームシーン用）
	int centerX_;
	int centerY_;

	// 水平・垂直の角度（ラジアン）
	float yaw_, pitch_;

	// カメラの位置
	VECTOR pos_;

	// カメラの角度(rad)
	VECTOR angles_;

	// 追従対象からのローカル座標
	VECTOR localPosFrom_;

	// 追従対象からのローカル座標の回転値
	VECTOR localRotFrom_;

	// カメラの前方向
	VECTOR forward_ = { 0,0,0 };

	// ゲーム内フラグ
	bool isInGame_;

	float controlSensi_;
};