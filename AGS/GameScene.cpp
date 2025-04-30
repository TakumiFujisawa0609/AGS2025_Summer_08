#include "Application.h"
#include "StageBase.h"
#include "Camera.h"
#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerShot.h"
#include "Blast.h"
#include "Collision.h"
#include "InputManager.h"
#include "SoundManager.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

//初期化処理
void GameScene::Init(void)
{
	// プレイヤー
	player_ = new Player();
	player_->Init(this);

	// カメラ
	camera_ = new Camera();
	camera_->Init(player_);

	//ステージ
	stage_ = new Stage();
	stage_->Init(camera_);

	// 敵
	enemy_ = new Enemy();
	enemy_->Init(this, camera_);

	// プレイヤー弾
	pShot_ = new PlayerShot();
	pShot_->Init(player_);

	// 爆発
	blast_ = new Blast();
	blast_->Init(enemy_);

	// 衝突
	collision_ = new Collision();
	collision_->Init(player_, enemy_, blast_, pShot_);

	// ゲームオーバー画面の画像を読み込む
	gameOverId_ = LoadGraph("Data/Image/GameOver.png");
	// ゲームクリア画面の画像を読み込む
	gameClearId_ = LoadGraph("Data/Image/GameClear.png");

	// ゲームクリアフラグの初期化
	isGameClear_ = false;
}

// 更新処理
void GameScene::Update(void)
{
	// ステージ
	stage_->Update();

	// カメラ
	camera_->Update();

	// プレイヤー
	player_->Update();
	// 敵
	enemy_->Update();
	// プレイヤー弾
	pShot_->Update();


	// 衝突
	collision_->Update();

	// 爆発
	blast_->Update();
}

// 描画処理
void GameScene::Draw(void)
{
	//ステージ
	stage_->Draw();

	//プレイヤー
	player_->Draw();

	// 敵	
	enemy_->Draw();

	// プレイヤー弾
	pShot_->Draw();

	// 衝突
	collision_->Draw();

	// 爆発
	blast_->Draw();

}

//解放処理
void GameScene::Release(void)
{
	//　ステージ
	stage_->Release();
	delete stage_;

	//　カメラ
	camera_->Release();
	delete camera_;

	//　プレイヤー
	player_->Release();
	delete player_;

	// 敵
	enemy_->Release();
	delete enemy_;

	// 弾
	pShot_->Release();
	delete pShot_;

	// 衝突
	collision_->Release();
	delete collision_;

	// 爆発
	blast_->Release();
	delete blast_;
}