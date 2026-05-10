#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
class StageBase;
class Camera;
class Player;
class PlayerShot;
class Blood;
class EnemyManager;
class ItemManager;
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

	void GameOver();

	void View();
	void Reticule();

	void Pause(void);//ポーズ画面
	void PauseDraw(void);

	void ClearTime();
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

	//testゲームシーン
	int testGameSceneImg_;
	//ポーズ背景
	int pauseImg_;
	//タスクシーン
	int taskuImg_;

	
	//マウス位置
	Vector2 mousePos_;


	int pauseSpan_;
	bool pauseSpanAlive_ = false;

	//ゲームオーバー画像ハンドル
	int gameOverImg_;
	//ゲームオーバーフラグ
	bool isGameOver = false;
	//ポーズフラグ
	bool isPauseAlive;
	//ポーズの初期読み込みハンドル
	bool isPauseInit;
	
	float gameOverTimer_;

	
	float clearTime_;      // プレイ開始からの経過時間

	int order1_;
};