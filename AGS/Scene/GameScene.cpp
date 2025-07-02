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
#include "../Object/Button/ReturnButton.h"
#include "../Object/Button/PauseExit.h"
#include "../Object/Button/TitleButton.h"

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
	pShot_->Init(camera_, player_);
	item_->Init(player_, pShot_);
	blood_->Init();
	collision_->Init(player_, stage_, enemy_, blood_, pShot_, camera_, item_);

	gameOverImg_ = LoadGraph("Data/Image/die.png");
	pauseImg_ = LoadGraph("Data/Image/Button/Pause.png");
	taskuImg_ = LoadGraph("Data/Image/Button/Pause.png");

	isPauseAlive = false;
	isPauseInit = false;

	clearTime_ = 0.0f;
	gameOverTimer_ = 0.0f;
}

// 更新処理
void GameScene::Update(void)
{
	// ポーズの更新
	Pause();

	// ポーズ中だったら処理しない
	if (isPauseAlive == true)
		return;

	// １つ目のワクチン回収時
	if (item_->IsShowingGetVaccine() || item_->IsShowingGetShot() || item_->IsShowingGetKit())
	{
		// ワクチン画像表示中は更新しない
		return;
	}

	SoundManager::GetInstance()->PlayBgm1();

	// プレイヤー生きてるかで分岐
	if (player_->GetAlive())
	{
		player_->Update(camera_->GetAngles());
		camera_->Update(); // 通常カメラ
	}
	else
	{
		camera_->UpdateDeathCamera(); // 死亡時カメラ演出

		SoundManager::GetInstance()->StopBgm1();
	}

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

	pShot_->Update();

	item_->Update();

	if (isGameOver)
	{
		// 時間を加算（1フレームあたりの経過時間）
		gameOverTimer_ += SceneManager::GetInstance()->GetDeltaTime();

		if (gameOverTimer_ >= 6.0f)
		{

			SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::TITLE);
		}
	}

	// クリアタイム
	ClearTime();
}

// 描画処理
void GameScene::Draw(void)
{
	stage_->Draw();

	player_->Draw();

	//grid_->Draw();

	enemy_->Draw();

	// 血
	blood_->Draw();

	// 景色
	View();

	camera_->Draw();

	pShot_->Draw();

	item_->Draw();

	// 血
	blood_->Draw();

	// レティクル
	Reticule();

	collision_->Draw();

	// リロードキーの表示
	pShot_->KeyDraw();

	GameOver();

	if (isPauseAlive == true)
	{
		//ポーズ画面の描画
		PauseDraw();
	}
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
	static float deathTimer = 0.0f;
	static bool isSEPlayed = false;

	bool isAliveP = player_->GetAlive();
	float deltaTime = SceneManager::GetInstance()->GetDeltaTime();

	if (!isAliveP)
	{
		isGameOver = true;
		deathTimer += deltaTime;

		float fadeStart = 2.0f;
		float showDuration = 2.0f;

		if (deathTimer >= fadeStart)
		{
			// フェードイン進行
			float t = (deathTimer - fadeStart) / showDuration;
			if (t > 1.0f) t = 1.0f;

			// ここでt==0.0になる瞬間が「ちょうど画像を表示し始めたタイミング」
			if (!isSEPlayed && t <= 0.01f)
			{
				SoundManager::GetInstance()->PlayImpact();
				isSEPlayed = true;
			}

			float eased = t * t * (3 - 2 * t);  // easeInOut
			int alpha = static_cast<int>(255 * eased);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawRotaGraph(958, 538, 1.0f, 0.0f, gameOverImg_, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else
	{
		// プレイヤーが生きている間はフラグをリセット（リトライ対応）
		deathTimer = 0.0f;
		isSEPlayed = false;
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
	DrawCircle(centerX, centerY, 280, GetColor(255, 255, 200), TRUE);
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

void GameScene::Pause(void)
{

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_ESCAPE))
	{
		isPauseAlive = true;
		
	}
	

	//ポーズ画面の継続確認
	if (isPauseAlive == true)
	{
		//ポーズの初期化
		if (isPauseInit == false)
		{

			pauseExit_ = new PauseExit(Application::SCREEN_SIZE_X/2, 850, 500, 200);
			pauseExit_->Init();

			returnButton_ = new ReturnButton(Application::SCREEN_SIZE_X / 2, 450, 500, 200);
			returnButton_->Init();

			titleButton_ = new TitleButton(Application::SCREEN_SIZE_X / 2, 650, 500, 200);
			titleButton_ -> Init();

			isPauseInit = true;
			return;
		}
	}
	// ここでEscapeキー判定を追加する
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_ESCAPE))
	{
		isPauseAlive = false;
		isPauseInit = false;  
		SetMouseDispFlag(false);
		return;
	}

	//初期化終わったおわっているか確認
	if (isPauseInit == true && isPauseAlive == true)
	{
		SetMouseDispFlag(true);
		GetMousePoint(&mousePos_X, &mousePos_Y);
		//ボタン更新
		pauseExit_->Update();
		returnButton_->Update();
		titleButton_->Update();

		if (pauseExit_->GetButtonState() == PauseExit::BUTTON_STATE::DISABLED)
		{
			SceneManager::GetInstance()->SetGameEnd();
			SetMouseDispFlag(false);
		}

		if (returnButton_->GetButtonState() == ReturnButton::BUTTON_STATE::DISABLED)
		{
			isPauseAlive = false;
			SetMouseDispFlag(false);
		}


		if (titleButton_->GetButtonState() == ReturnButton::BUTTON_STATE::DISABLED)
		{
			SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::TITLE);
	
		}
		
		
	}

}

void GameScene::PauseDraw(void)
{
	DrawGraph(0, 0, pauseImg_, true);


	pauseExit_->Draw();
	returnButton_->Draw();
	titleButton_->Draw();
}

void GameScene::ClearTime()
{
	if (!collision_->GetClear())  // ポーズ中でなく、クリアしていなければ時間を進める
	{
		clearTime_ += SceneManager::GetInstance()->GetDeltaTime();
	}

	if (collision_->GetClear())
	{
		SoundManager::GetInstance()->StopWalk();

		SceneManager::GetInstance()->SetClearTime(clearTime_);

		// ワクチンがすべて拾われていたらゲームクリアへ遷移
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	}
}


