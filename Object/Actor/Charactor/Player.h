#pragma once
#include "CharactorBase.h"

class Player : public CharactorBase
{
public:

	enum class ANIM_TYPE
	{
		IDLE,
		RUN,
		FAST_RUN,
		JUMP,
	};

	Player(void);

	~Player(void) override;

	// 描画
	void Draw(void) override;

protected:

	// リソースロード
	virtual void InitLoad(void) override;

	// 大きさ、回転、座標の初期化
	virtual void InitTransform(void) override;

	// 衝突判定の初期化
	virtual void InitCollider(void) override;

	// アニメーションの初期化
	virtual void InitAnimation(void) override;

	// 初期化後の個別処理
	virtual void InitPost(void) override;

private:

	// 回復中か
	bool isHealing_;

	// 移動速度（通常）
	static constexpr float SPEED_MOVE = 5.0f;

	// 移動速度（ダッシュ）
	static constexpr float SPEED_DASH = 10.0f;

	// 移動速度
	static constexpr float SPEED_MOVE = 8.5f;
	// 移動速度（回復中）
	static constexpr float SPEED_MOVE_HEALING = SPEED_MOVE / 2;

	// 衝突判定用線分開始
	static constexpr VECTOR COL_LINE_START_LOCAL_POS = { 0.0f, 80.0f, 0.0f };
	// 衝突判定用線分終了
	static constexpr VECTOR COL_LINE_END_LOCAL_POS = { 0.0f, -10.0f, 0.0f };

	// 衝突判定用カプセル上部球体
	static constexpr VECTOR COL_CAPSULE_TOP_LOCAL_POS = { 0.0f, 110.0f, 0.0f };
	// 衝突判定用カプセル下部球体
	static constexpr VECTOR COL_CAPSULE_DOWN_LOCAL_POS = { 0.0f, 50.0f, 0.0f };

	// 衝突判定用カプセル
	static constexpr float COL_CAPSULE_RADIUS = 20.0f;

	// 移動処理
	void ProcessMove(void);

	// 更新系
	virtual void UpdateProcess(void) override;
	virtual void UpdateProcessPost(void) override;

	// 衝突判定
	void CollisionReserve(void) override;
};

