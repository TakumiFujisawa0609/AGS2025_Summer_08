#pragma once

class Player
{
public:
	static constexpr VECTOR DEFAULT_POS = { 0.0f,0.0f,0.0f };
	static constexpr VECTOR DEFAULT_ANGLE = { 0.0f,0.0f,0.0f };
	static constexpr float MOVE_SPEED = 8.5f;

	// 初期モデル補正角度
	static constexpr VECTOR INIT_MODEL_ROT_OFFSET = { 0.0f, DX_PI_F, 0.0f };

	// ヒットポイント
	static constexpr int DEFAULT_HP = 2;

	void Init(void);
	void Update(VECTOR angle);
	void Draw(void);
	void Release(void);

	// HP
	void Hp(void);

	// モデルの座標情報を反映させる
	void ModelReflect();

	void Damage(int damage);
	void DamageEffect();

	// 移動停止
	void SetStop(bool isStop);

	// 回復
	void Heal(int heal);


	VECTOR GetPPos(void);
	VECTOR GetMovedPos(void);

	bool GetAlive(void);
	int GetHp();
	int GetHeal();
private:

	// プレイヤーモデル
	int modelId_;
	
	// プレイヤーの移動前座標
	VECTOR movedPos_;
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

	// 移動停止フラグ
	bool isStop_;

	// 生存フラグ
	bool isAlive_;

	// 体力
	int hp_;

	// 回復可能回数
	int heal_;

	bool isHeal_;
	bool isHoldingQ_ = false;  // Q長押し中かどうか
};