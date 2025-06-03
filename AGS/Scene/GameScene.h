#pragma once
#include "SceneBase.h"
class StageBase;
class Camera;
class Player;
class PlayerShot;
class Blood;
class EnemyManager;
class Collision;
class Grid;


class GameScene : public SceneBase
{

public:

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:


	// プレイヤー
	Player* player_;

	// ステージ
	StageBase* stage_;

	// カメラ
	Camera* camera_;

	// 敵
	EnemyManager* enemy_;

	// 弾
	PlayerShot* pShot_;

	// 爆発
	Blood* blood_;

	// 衝突
	Collision* collision_;

	// グリッド
	Grid* grid_;

	//testゲームシーン
	int testGameSceneImg_;

	
};