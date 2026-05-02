#pragma once
#include "../ActorBase.h"
class AnimationController;

class CharactorBase : public ActorBase
{
public:

	// 衝突判定種別
	enum class COLLIDER_TYPE
	{
		GROUND_LINE,
		CAPSULE,
		VIEW_RANGE,
		MAX,
	};

	// コンストラクタ
	CharactorBase(void);

	// デストラクタ
	virtual ~CharactorBase(void);

	// 更新
	virtual void Update(void) override;

	virtual void Draw(void) override;

	void Release() override;

protected:

	// アニメーション
	AnimationController* animController_;

	// キャラの前方向 (カメラの前方向)
	VECTOR faceDir_;

	// 移動方向
	VECTOR moveDir_;

	// 移動スピード
	float moveSpeed_;

	// 移動量
	VECTOR movePow_;

	// 移動前の座標
	VECTOR prevPos_;

	// 丸影画像
	int imgShadow_;

	// 衝突時の押し戻し試行回数
	static constexpr int CNT_TRY_COLLISION = 20;
	// 衝突時の押し戻し量
	static constexpr float COLLISION_BACK_DIS = 1.0f;

	// リソースロード
	virtual void InitLoad(void) override;

	// 更新系
	virtual void UpdateProcess(void) = 0;
	virtual void UpdateProcessPost(void) = 0;

	// 方向に応じた回転
	void Rotate(void);

	// 衝突判定
	virtual void CollisionReserve(void) {};
	void Collision(void);
	void CollisionCapsule(void);

	// 丸影描画
	void DrawShadow(void);
	// リアルシャドウ描画
	void DrawRealShadow(void);
};

