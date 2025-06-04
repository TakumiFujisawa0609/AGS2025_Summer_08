#pragma once
class AnimControl;
class Player;


class EnemyBase
{
public:

	enum class TYPE
	{
		NORMAL,
		MAX
	};

	enum class STATE
	{
		IDLE,		// 待機
		WALK,		// 歩き
		RUN,		// 走り
		ATTACK,		// 攻撃
		DIE,		// 死亡
	};

	// スポーン位置
	struct SpawnPoint
	{
		VECTOR pos;
	};

	static constexpr SpawnPoint spawnPoints[4] = {
		{100.0f, 0.0f, 400.0f},
		{700.0f, 0.0f, 400.0f},
		{-700.0f, 0.0f, 1300.0f},
		{700.0f, 0.0f, 1300.0f}
	};

	// 敵初期位置
	static constexpr VECTOR INIT_ENEMY_POS = { 0.0f, 0.0f, 250.0f };
	// 敵初期角度
	static constexpr VECTOR INIT_ENEMY_ANGLE = { 0.0f, 0.0f, 0.0f };

	// 移動速度
	static constexpr float MOVE_WALK_SPEED = 2.0f;	// 歩き
	static constexpr float MOVE_RUN_SPEED = 4.0f;	// 走り

	// アニメーションが切り替わる距離
	static constexpr float WALK_DISTANCE = 1500.0f;	// 歩き
	static constexpr float RUN_DISTANCE = 1000.0f;	// 走り
	static constexpr float ATTACK_DISTANCE = 150.0f;	// 攻撃

	EnemyBase();
	virtual ~EnemyBase();

	void Init(TYPE type, int baseModelId, Player* player);	// 初期化
	void Update();	// 更新
	void Draw();	// 描画
	void Release();	// 解放

	void ModelReflect();	// モデルの座標情報などを反映させる。

	int GetModelId() const; // モデルID取得
	VECTOR GetPos() const; // 敵座標取得
	VECTOR GetMovedPos() const; // 移動予定位置取得
	
	void SetPos(VECTOR pos);

	void SetStop(bool isStop);

	//void TakeDamage(int damage);

	void ChasePlayer();

	void LookPlayer();
	void ChangeState();	// アニメーション変更
	void UpdateBehavior();	// プレイヤー追尾

	void PlayIdle();

	void PlayWalk();

	void PlayRun();

	void PlayAttack();

	void PlayDie();

	bool GetAlive();
	void SetAlive(bool isAlive);

	EnemyBase::STATE GetState() const;

	float GetAnimRate();

protected:

	AnimControl* anim_;	// アニメーションクラス
	STATE state_;	// 敵の状態

	// 種別
	TYPE type_;

	Player* player_;	// プレイヤーのポインタ

	// 敵モデルID
	int modelId_;

	// 敵座標
	VECTOR pos_;
	// 移動予定位置
	VECTOR movedPos_;
	VECTOR moveDir_;

	// 敵角度
	VECTOR angle_;

	// 敵のスピード
	float speed_;

	// 敵とプレイヤーの距離
	float dist_ = 0.0f;

	//敵の停止フラグ
	bool isStop_ = false;

	// 生存判定
	bool isAlive_;

	

	// パラメータ設定(純粋仮想関数)
	virtual void SetParam() = 0;
};
