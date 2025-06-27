#pragma once
#include "SceneBase.h"
class StageBase;
class Camera;
class Player;
class PlayerShot;
class Blood;
class EnemyManager;
class ItemManager;
class Collision;
class Grid;
class ExitButton;

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

	void GameOver();

	void View();
	void Reticule();

	void Pause(void);//ポーズ画面
	void PauseDraw(void);
private:


	// プレイヤー
	Player* player_;
	// ステージ
	StageBase* stage_;
	// カメラ
	Camera* camera_;
	// 敵
	EnemyManager* enemy_;
	// アイテム
	ItemManager* item_;
	// 弾
	PlayerShot* pShot_;
	// 爆発
	Blood* blood_;
	// 衝突
	Collision* collision_;
	// グリッド
	Grid* grid_;
	//ゲーム終了ボタン
	ExitButton* exitButton_;

	//testゲームシーン
	int testGameSceneImg_;
	//ポーズ背景
	int pauseImg_;
	//タスクシーン
	int taskuImg_;

	
	//マウス位置
	int mousePos_X;
	int mousePos_Y;



	int gameOverImg_;
	bool isGameOver = false;
	bool isPauseAlive;
	bool isPauseInit;
	
	float gameOverTimer_ = 0.0f;

	

};