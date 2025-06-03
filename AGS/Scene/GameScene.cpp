#include "../Manager/Application.h"
#include "../Object/Camera.h"
#include "../Object/StageBase.h"
#include "../Object/Player.h"
#include "../Manager/EnemyManager.h"
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
	enemy_ = new EnemyManager(player_);
	stage_ = new StageBase();
	pShot_ = new PlayerShot();
	blood_ = new Blood();
	collision_ = new Collision();

	player_->Init();
	camera_->Init(player_);
	enemy_->Init();
	stage_->Init();
	pShot_->Init(camera_);
	blood_->Init();
	collision_->Init(player_, stage_, enemy_, blood_, pShot_, camera_);
}

// 更新処理
void GameScene::Update(void)
{
	player_->Update(camera_->GetAngles());

	enemy_->Update();

	// 血
	blood_->Update();

	// 当たり判定
	collision_->Update();

	// 当たり判定→プレイヤー座標更新
	player_->ModelReflect();
	
	// 敵取得
	const auto& enemies = enemy_->GetEnemies();
	// 連想配列（map）を for で回す
	for (auto pair : enemies)
	{
		// pair.first : EnemyBase::TYPE（型）
		// pair.second : std::vector<EnemyBase*>（敵リスト）
		for (EnemyBase* enemy : pair.second)
		{
			// 当たり判定→敵座標更新
			enemy->ModelReflect();
		}
	}

	camera_->Update();

	pShot_->Update();

}

// 描画処理
void GameScene::Draw(void)
{
	stage_->Draw();

	player_->Draw();

	grid_->Draw();

	enemy_->Draw();

	camera_->Draw();

	pShot_->Draw();

	// 血
	blood_->Draw();

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

	pShot_->Release();
	delete pShot_;

	blood_->Release();
	delete blood_;
}