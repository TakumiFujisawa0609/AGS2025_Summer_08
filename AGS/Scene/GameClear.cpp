#include <DxLib.h>
#include "../Manager/Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "GameClear.h"

GameClear::GameClear(void)
{
}

GameClear::~GameClear(void)
{
}

void GameClear::Init(void)
{
	gameClearImg_ = LoadGraph("Data/Image/gameclear1.png");
	resultImg_ = LoadGraph("Data/Image/result.png");

	clearMovieHundle_ = LoadGraph("Data/Sound/clear.mp4");
	PlayMovieToGraph(clearMovieHundle_);

	clearTime_ = 0.0f;
	movieTimer_ = 0.0f;

	isPause_ = false;
	isResult_ = false;

	fontHandle_ = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE);
	//fontHandle_ = CreateFontToHandle("MS ゴシック", 50, 1, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void GameClear::Update(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

	movieTimer_ += SceneManager::GetInstance()->GetDeltaTime();

	// 8秒経ったら止める
	if (!isPause_ && movieTimer_ >= 8.0f)
	{
		PauseMovieToGraph(clearMovieHundle_);

		isPause_ = true;
		isResult_ = true;
	}
}

void GameClear::Draw(void)
{
	// ムービー描画
	DrawGraph(0, 0, clearMovieHundle_, TRUE);

	if (isPause_)
	{
		if (isResult_)
		{
			SoundManager::GetInstance()->PlayPause();
			isResult_ = false;
		}
		SoundManager::GetInstance()->PlayClear();

		//DrawRotaGraph(950, 600, 0.6, 0.0f, resultImg_, true);
		DrawGraph(0, 15, resultImg_, true);
		SetFontSize(220);

		// クリアタイム-------------------------------------------------------------
		clearTime_ = SceneManager::GetInstance()->GetClearTime();
		DrawFormatStringToHandle(340, 320, GetColor(255, 255, 255), fontHandle_, "Clear Time : %.1f seconds", clearTime_);

		int enemyKillNumber = SceneManager::GetInstance()->GetEnemyKillNuber();
		DrawFormatStringToHandle(340, 450, GetColor(255, 255, 255), fontHandle_, "Zombies : %d killed", enemyKillNumber);
		
		float acc = SceneManager::GetInstance()->GetAccuracy();
		DrawFormatStringToHandle(340, 580, GetColor(255, 255, 255), fontHandle_, "Hit Rate : %.1f %%", acc * 100.0f);

		int headShotNumber = SceneManager::GetInstance()->GetHeadShotNumber();
		DrawFormatStringToHandle(340, 710, GetColor(255, 255, 255), fontHandle_, "Head Shot : %d hit", headShotNumber);
	}
}

void GameClear::Release(void)
{
	DeleteGraph(gameClearImg_);

	DeleteGraph(clearMovieHundle_);

	DeleteFontToHandle(fontHandle_);
}
