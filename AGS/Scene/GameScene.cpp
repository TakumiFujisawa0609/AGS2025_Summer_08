#include "../Manager/Application.h."
#include "../Object/StageBase.h"
#include "../Object/Camera.h"
#include "GameScene.h"
#include "../Object/Player.h"
#include "../Object/EnemyBase.h"
#include "../Object/PlayerShot.h"
#include "../Object/Blood.h"
#include "../Fanction/Collision.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

//‰Šú‰»ˆ—
void GameScene::Init(void)
{
	//testgame_ = LoadGraph("Image/testgame.png");

	camera_ = new Camera();
	camera_->Init(player_);

	enemy_ = new EnemyBase();
	enemy_->Init(this, camera_);
}

// XVˆ—
void GameScene::Update(void)
{
	camera_->Update();

	enemy_->Update();
}

// •`‰æˆ—
void GameScene::Draw(void)
{
	//DrawGraph(0,0,testgame_,true);

	enemy_->Draw();
}

//‰ð•úˆ—
void GameScene::Release(void)
{
	//DeleteGraph(testgame_);

	enemy_->Release();
}


