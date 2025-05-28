#pragma once

class Player
{
public:
	static constexpr VECTOR DEFAULT_POS = { 0.0f,0.0f,0.0f };
	static constexpr VECTOR DEFAULT_ANGLE = { 0.0f,0.0f,0.0f };
	static constexpr float MOVE_SPEED = 10.0f;

	// 初期モデル補正角度
	static constexpr VECTOR INIT_MODEL_ROT_OFFSET = { 0.0f, DX_PI_F, 0.0f };

	void Init(void);
	void Update(VECTOR angle);
	void Draw(void);
	void Release(void);

	void Dir();

	VECTOR GetPPos(void);
private:

	// プレイヤーモデル
	int modelId_;

	// プレイヤー座標
	VECTOR pos_;
	// 角度
	VECTOR angle_;

	// 移動ベクトル
	VECTOR moveVec_;

	// 移動ベクトルが生成する角度
	VECTOR moveVecRad_;

	// 角度
	VECTOR rot_;

	// 調整用初期角度
	VECTOR localRot_;

	// カメラの方向取得用
	VECTOR cameraAngle_;

	// 回転設定
	void SetRotation(void);

	// 移動関連
	// 移動操作
	void ProcessMove(VECTOR angle);
};