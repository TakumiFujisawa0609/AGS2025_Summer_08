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
	// テストゲームシーン
	testGameSceneImg_ = LoadGraph("image/TestGameScene.png");
}

// 更新処理
void GameScene::Update(void)
{
	
}

// 描画処理
void GameScene::Draw(void)
{
	DrawGraph(0, 0, testGameSceneImg_, true);

}

//解放処理
void GameScene::Release(void)
{
	DeleteGraph(testGameSceneImg_);
}