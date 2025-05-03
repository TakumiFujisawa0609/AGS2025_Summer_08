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


