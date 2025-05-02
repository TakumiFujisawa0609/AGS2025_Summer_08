#include "Application.h"
#include "StageBase.h"
#include "Camera.h"
#include "GameScene.h"
#include "Player.h"
#include "EnemyBase.h"
#include "PlayerShot.h"
#include "Blood.h"
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

	// 死んだらゲームオーバー画像描画
	if (!player_->GetIsAlivePlayer())
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1, 0, gameOverId_, true, false);
	}
	// ゲームクリアフラグが立ったらゲームクリア画像描画
	if (isGameClear_)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1, 0, gameClearId_, true, false);
	}
	//DrawFormatString(0, 300, 0xffffff, "ゲームクリアフラグ: %d", isGameClear_);
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

	// ゲームオーバー画像の解放
	DeleteGraph(gameOverId_);
	// ゲームクリア画像の解放
	DeleteGraph(gameClearId_);

}

// ゲームクリアフラグの設定
void GameScene::SetIsGameClear(bool isGameClear)
{
	isGameClear_ = isGameClear;
}
// // ゲームクリアフラグの取得
bool GameScene::GetIsGameClear(void)
{
	return isGameClear_;
}


