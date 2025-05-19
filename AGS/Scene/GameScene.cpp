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

//‰Šú‰»ˆ—
void GameScene::Init(void)
{
	player_ = new Player();
	player_->Init();

	stage_ = new StageBase();
	stage_->Init();

	camera_ = new Camera();
	camera_->Init(player_);

	enemy_ = new EnemyBase();
	enemy_->Init(player_);

	collision_ = new Collision();
	collision_->Init(player_, stage_, enemy_, blast_, pShot_);
}

// XVˆ—
void GameScene::Update(void)
{
	player_->Update();

	enemy_->Update();

	camera_->Update();

	collision_->Update();
}

// •`‰æˆ—
void GameScene::Draw(void)
{
	stage_->Draw();

	player_->Draw();

	grid_->Draw();
	enemy_->Draw();

	camera_->Draw();
}

//‰ð•úˆ—
void GameScene::Release(void)
{

	stage_->Release();
	delete stage_;

	player_->Release();
	delete player_;

	enemy_->Release();
	delete enemy_;

}