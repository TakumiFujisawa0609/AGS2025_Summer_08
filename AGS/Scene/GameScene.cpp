#include "../Manager/Application.h"
#include "../Object/Camera.h"
#include "../Object/StageBase.h"
#include "../Object/Player.h"
#include "../Object/EnemyBase.h"
#include "../Object/PlayerShot.h"
#include "../Object/Blood.h"
#include "../Common/Collision.h"
#include "../Common/Grid.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"
#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

//初期化処理
void GameScene::Init(void)
{
	player_ = new Player();
	camera_ = new Camera();
	enemy_ = new EnemyBase();
	stage_ = new StageBase();
	collision_ = new Collision();

	player_->Init();
	camera_->Init(player_);
	enemy_->Init(player_);
	stage_->Init();
	collision_->Init(player_, stage_, enemy_, blast_, pShot_);
}

// 更新処理
void GameScene::Update(void)
{
	player_->Update(camera_->GetAngles());

	enemy_->Update();

	camera_->Update();

	// 当たり判定
	collision_->Update();
	// 当たり判定→敵座標更新
	enemy_->ModelReflect();

}

// 描画処理
void GameScene::Draw(void)
{
	stage_->Draw();

	player_->Draw();

	grid_->Draw();
	enemy_->Draw();

	camera_->Draw();

	collision_->Draw();
}

//解放処理
void GameScene::Release(void)
{

	stage_->Release();
	delete stage_;

	player_->Release();
	delete player_;

	enemy_->Release();
	delete enemy_;

}