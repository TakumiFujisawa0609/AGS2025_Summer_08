#include "../Manager/Application.h"
#include "../Manager/SceneManager.h"
#include "../Object/Camera.h"
#include "../Object/StageBase.h"
#include "../Object/Player.h"
#include "../Manager/EnemyManager.h"
#include "../Manager/ItemManager.h"
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
	stage_ = new StageBase();
	player_ = new Player();
	camera_ = new Camera();
	enemy_ = new EnemyManager(player_);
	pShot_ = new PlayerShot();
	item_ = new ItemManager();
	blood_ = new Blood();
	collision_ = new Collision();

	stage_->Init();
	player_->Init();
	camera_->Init(player_);
	enemy_->Init();
	pShot_->Init(camera_);
	item_->Init(player_, pShot_);
	blood_->Init();
	collision_->Init(player_, stage_, enemy_, blood_, pShot_, camera_, item_);

	gameOverImg_ = LoadGraph("Data/Image/gameover.png");
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

	item_->Update();

	gameOverTimer_ += SceneManager::GetInstance()->GetDeltaTime();

	if (isGameOver)
	{
		if (gameOverTimer_ >= 3.0f)
		{
			SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::TITLE);
		}
	}

}

// 描画処理
void GameScene::Draw(void)
{
	stage_->Draw();

	player_->Draw();

	//grid_->Draw();

	enemy_->Draw();

	// 景色
	//View();

	camera_->Draw();

	pShot_->Draw();

	item_->Draw();

	// 血
	blood_->Draw();

	collision_->Draw();

	// リロードキーの表示
	pShot_->KeyDraw();

	// レティクル
	Reticule();

	GameOver();

	
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

	item_->Release();
	delete item_;

	blood_->Release();
	delete blood_;

	DeleteGraph(gameOverImg_);
}

void GameScene::GameOver()
{
	bool isAliveP = true;
	isAliveP = player_->GetAlive();

	if (isAliveP == false)
	{
		float scale = 1.1f;  // 縮小
		DrawRotaGraph(958, 538, scale, 0.0f, gameOverImg_, true);

		isGameOver = true;

	}
}

void GameScene::View()
{
	// 2. 加算合成で中心を光らせる（スポットライト風）
	int centerX = Application::SCREEN_SIZE_X / 2;
	int centerY = Application::SCREEN_SIZE_Y / 2;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150); // 薄暗くする
	DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 円の明かり（ここは好みに応じて画像でも可）
	SetDrawBlendMode(DX_BLENDMODE_ADD, 120);
	DrawCircle(centerX, centerY, 200, GetColor(255, 255, 200), TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameScene::Reticule()
{
	int centerX_ = Application::SCREEN_SIZE_X / 2;
	int centerY_ = Application::SCREEN_SIZE_Y / 2;

	int size = 8;    // 各矢印の長さ
	int gap = 4;         // 中心からの間隔
	int color = GetColor(255, 255, 255);

	// 上
	DrawLine(centerX_, centerY_ - gap, centerX_, centerY_ - (gap + size), color);
	// 下
	DrawLine(centerX_, centerY_ + gap, centerX_, centerY_ + (gap + size), color);
	// 左
	DrawLine(centerX_ - gap, centerY_, centerX_ - (gap + size), centerY_, color);
	// 右
	DrawLine(centerX_ + gap, centerY_, centerX_ + (gap + size), centerY_, color);
}


