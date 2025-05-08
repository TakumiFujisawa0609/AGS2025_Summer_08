<<<<<<< HEAD
#include "../Manager/Application.h"
=======
#include "../Manager/Application.h."
#include "../Object/StageBase.h"
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
#include "../Object/Camera.h"
#include "GameScene.h"
#include "../Object/Player.h"
#include "../Object/EnemyBase.h"
#include "../Object/PlayerShot.h"
#include "../Object/Blood.h"
<<<<<<< HEAD
#include "../Function/Collision.h"
#include "../Function/Grid.h"
=======
#include "../Fanction/Collision.h"
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
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
<<<<<<< HEAD
	// テストゲームシーン
	//testGameSceneImg_ = LoadGraph("Data/image/TestGameScene.png");
=======
	//testgame_ = LoadGraph("Image/testgame.png");
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70

	camera_ = new Camera();
	camera_->Init(player_);

	enemy_ = new EnemyBase();
<<<<<<< HEAD
	enemy_->Init();
=======
	enemy_->Init(this, camera_);
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
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
<<<<<<< HEAD
	//DrawGraph(0, 0, testGameSceneImg_, true);

	enemy_->Draw();

	grid_->Draw();
=======
	//DrawGraph(0,0,testgame_,true);

	enemy_->Draw();
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
}

//解放処理
void GameScene::Release(void)
{
<<<<<<< HEAD
	//DeleteGraph(testGameSceneImg_);

	enemy_->Release();
}
=======
	//DeleteGraph(testgame_);

	enemy_->Release();
}


>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
