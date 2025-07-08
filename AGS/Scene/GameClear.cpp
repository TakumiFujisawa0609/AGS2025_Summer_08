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
		SoundManager::GetInstance()->PlayPaper();

		isPause_ = true;
	}
}

void GameClear::Draw(void)
{
	// ムービー描画
	DrawGraph(0, 0, clearMovieHundle_, TRUE);

	if (isPause_)
	{
		SoundManager::GetInstance()->PlayClear();
		DrawGraph(0, 0, resultImg_, true);

		isPause_ = false;
	}

	//clearTime_ = SceneManager::GetInstance()->GetClearTime();

	//SetFontSize(100);
	//DrawFormatString(1300, Application::SCREEN_SIZE_Y / 2 - 120, 0xffffff, "ClearTime");

	//// 小数点以下は文字列で分割して描画
	//int intPart = static_cast<int>(clearTime_);
	//int decimalPart = static_cast<int>((clearTime_ - intPart) * 100);  // 小数点以下2桁

	//// 整数部＋小数点を描画
	//char timeStr[32];
	//snprintf(timeStr, sizeof(timeStr), "%d.", intPart);
	//int intPartWidth = GetDrawStringWidth(timeStr, strlen(timeStr));
	//DrawFormatString(1400, Application::SCREEN_SIZE_Y / 2, 0xffffff, "%s", timeStr);

	//// 小数部は少し小さくして整数部の右に少しスペースを空けて描画
	//SetFontSize(60);
	//snprintf(timeStr, sizeof(timeStr), "%02d", decimalPart);
	//DrawFormatString(1380 + intPartWidth, Application::SCREEN_SIZE_Y / 2 + 32, 0xffffff, "%s秒", timeStr);
}

void GameClear::Release(void)
{
	DeleteGraph(gameClearImg_);

	DeleteGraph(clearMovieHundle_);
}
