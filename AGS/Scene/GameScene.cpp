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
	testgame_ = LoadGraph("Image/testgame.png");
}

// XVˆ—
void GameScene::Update(void)
{

}

// •`‰æˆ—
void GameScene::Draw(void)
{
	DrawGraph(0,0,testgame_,true);
}

//‰ğ•úˆ—
void GameScene::Release(void)
{
	DeleteGraph(testgame_);
}


