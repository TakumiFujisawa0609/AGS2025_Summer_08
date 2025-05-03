#pragma once
#include "SceneBase.h"
class Stage;
class Camera;
class Player;
class PlayerShot;
class Blood;
class EnemyBase;
class EnemyShot;
class Collision;


class GameScene : public SceneBase
{

public:

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void)	override;
	void Update(void) override;
	void Draw(void)	override;
	void Release(void) override;

private:

	// ステージ
	Stage* stage_;

	// カメラ
	Camera* camera_;

	// プレイヤー
	Player* player_;

	// 敵
	EnemyBase* enemy_;

	// 弾
	PlayerShot* pShot_;

	// 敵の弾
	EnemyShot* eShot_;

	// 爆発
	Blood* blood_;

	// 衝突
	Collision* collision_;

	int testgame_;
};
