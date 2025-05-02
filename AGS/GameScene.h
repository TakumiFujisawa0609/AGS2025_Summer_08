#pragma once
#include "SceneBase.h"
class Stage;
class Camera;
class Player;
class PlayerShot;
class Blast;
class Enemy;
class Collision;


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

	// ゲームクリアフラグの設定
	void SetIsGameClear(bool isGameClear);
	// ゲームクリアフラグの取得
	bool GetIsGameClear(void);

private:
	// プレイヤー
	Player* player_;

	// ステージ
	Stage* stage_;

	// カメラ
	Camera* camera_;

	// 敵
	Enemy* enemy_;

	// 弾
	PlayerShot* pShot_;

	// 爆発
	Blast* blast_;

	// 衝突
	Collision* collision_;

	//testゲームシーン
	int testGameSceneImg_;

	
};