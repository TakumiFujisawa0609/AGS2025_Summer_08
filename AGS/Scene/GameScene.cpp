#include "../Manager/Application.h"
#include "../Object/Camera.h"
#include "GameScene.h"
#include "../Object/Player.h"
#include "../Object/EnemyBase.h"
#include "../Object/PlayerShot.h"
#include "../Object/Blood.h"
#include "../Function/Collision.h"
#include "../Function/Grid.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

//初期化処理
void GameScene::Init(void)
{
	// テストゲームシーン
	//testGameSceneImg_ = LoadGraph("Data/image/TestGameScene.png");

	camera_ = new Camera();
	camera_->Init(player_);

	enemy_ = new EnemyBase();
	enemy_->Init();
}

// 更新処理
void GameScene::Update(void)
{
	camera_->Update();

	enemy_->Update();
}

// 描画処理
void GameScene::Draw(void)
{
	//DrawGraph(0, 0, testGameSceneImg_, true);

	enemy_->Draw();

	grid_->Draw();
}

//解放処理
void GameScene::Release(void)
{
	//DeleteGraph(testGameSceneImg_);

	enemy_->Release();
}