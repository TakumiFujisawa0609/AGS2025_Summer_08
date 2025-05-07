#include "../Manager/Application.h"
#include "../Object/PlayerShot.h"
#include "../Object/Camera.h"
#include "GameScene.h"
#include "../Object/Player.h"
#include "../Object/EnemyBase.h"
#include "../Object/PlayerShot.h"
#include "../Object/Blood.h"
#include "../Function/Collision.h"
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