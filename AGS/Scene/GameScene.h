#pragma once
#include "SceneBase.h"
class Stage;
class Camera;
class Player;
class PlayerShot;
<<<<<<< HEAD
class Blast;
class EnemyBase;
=======
class Blood;
class EnemyBase;
class EnemyShot;
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
class Collision;
class Grid;


class GameScene : public SceneBase
{

public:

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

<<<<<<< HEAD
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:


	// プレイヤー
	Player* player_;
=======
	void Init(void)	override;
	void Update(void) override;
	void Draw(void)	override;
	void Release(void) override;

private:
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70

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

<<<<<<< HEAD
	// グリッド
	Grid* grid_;

	//testゲームシーン
	int testGameSceneImg_;

	
};
=======
	int testgame_;
};
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
