#include <cstring>
#include <DxLib.h>

// DxLibのmin/maxマクロを無効化
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include <algorithm> // std::min / max を安全に使う
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

	fontHandle1_ = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE);
	fontHandle2_ = CreateFontToHandle("メイリオ", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE);
	fontHandle3_ = CreateFontToHandle("メイリオ", 165, 1, DX_FONTTYPE_ANTIALIASING_EDGE);
	//fontHandle_ = CreateFontToHandle("MS ゴシック", 50, 1, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void GameClear::Update(void)
{

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
		SetMouseDispFlag(true);
		if (CheckHitKey(KEY_INPUT_SPACE) || (GetMouseInput() & MOUSE_INPUT_LEFT))
		{
			// スペースキーが押下されたら、ゲームシーンへ遷移する
			SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::TITLE);
		}
		SoundManager::GetInstance()->PlayClear();

		//DrawRotaGraph(950, 600, 0.6, 0.0f, resultImg_, true);
		DrawGraph(0, 15, resultImg_, true);
		SetFontSize(200);

		// --- クリアタイム ---
		int totalSec = static_cast<int>(SceneManager::GetInstance()->GetClearTime());
		int minutes = totalSec / 60;
		int seconds = totalSec % 60;

		char timeStr[16];
		snprintf(timeStr, sizeof(timeStr), "%02d:%02d", minutes, seconds);
		DrawFormatStringToHandle(300, 300, GetColor(255, 255, 255), fontHandle1_, "Clear Time   %s", timeStr);

		// 各項目取得
		int enemyKillNumber = SceneManager::GetInstance()->GetEnemyKillNuber();
		DrawFormatStringToHandle(350, 450, GetColor(255, 255, 255), fontHandle1_, "Zombies : %d killed", enemyKillNumber);

		float acc = SceneManager::GetInstance()->GetAccuracy();
		DrawFormatStringToHandle(350, 600, GetColor(255, 255, 255), fontHandle1_, "Hit Rate : %.1f%%", acc * 100.0f);

		int headShotNumber = SceneManager::GetInstance()->GetHeadShotNumber();
		DrawFormatStringToHandle(350, 750, GetColor(255, 255, 255), fontHandle1_, "Head Shot : %d hits", headShotNumber);

		// 時間スコア（30秒ごとの段階制、最大10分）
		const int maxTimeScore = 1500 * 180;  // 満点スコア（3分）
		const int maxClearTime = 600;         // 10分で0点
		int step = totalSec / 30;
		int maxSteps = maxClearTime / 30;
		if (step > maxSteps) step = maxSteps;
		int timeScore = maxTimeScore * (maxSteps - step) / maxSteps;

		// 残りスコア
		int killScore = std::min(enemyKillNumber, 50) * 10000;
		int accScore = static_cast<int>(std::min(acc, 0.1f) * 99999);
		int headScore = std::min(headShotNumber, 50) * 10000;
		int totalScore = std::min(timeScore + killScore + accScore + headScore, 999999);

		// スコア表示
		DrawFormatStringToHandle(1150, 300, GetColor(255, 255, 255), fontHandle2_, "SCORE");
		DrawFormatStringToHandle(1130, 500, GetColor(255, 255, 255), fontHandle2_, "%06d", totalScore);

		// ランク表示用の色定義
		const int COLOR_S = GetColor(255, 215, 0);   // ゴールド
		const int COLOR_A = GetColor(255, 0, 0);     // レッド
		const int COLOR_B = GetColor(0, 0, 255);     // 青
		const int COLOR_C = GetColor(255, 255, 0);   // 黄色

		// ランク判定
		char rankChar = 'C';           // 初期はC
		int rankColor = COLOR_C;       // Cの色で初期化

		if (totalScore >= 500000) {
			rankChar = 'S';
			rankColor = COLOR_S;
		}
		else if (totalScore >= 450000) {
			rankChar = 'A';
			rankColor = COLOR_A;
		}
		else if (totalScore >= 400000) {
			rankChar = 'B';
			rankColor = COLOR_B;
		}
		// それ以外はC（黄色）

		// 描画
		DrawFormatStringToHandle(1265, 650, rankColor, fontHandle3_, "%c", rankChar);

		// ランク文字描画位置
		int rankX = 1285;
		int rankY = 650;

		// 下線を描画（フォントの高さ+10程度下）
		int lineY = rankY + 153;
		DrawLine(rankX - 25, lineY, rankX + 105, lineY, 0xffffff, 5); // 太さ5の直線
	}
}

void GameClear::Release(void)
{
	DeleteGraph(gameClearImg_);

	DeleteGraph(clearMovieHundle_);

	DeleteFontToHandle(fontHandle1_);
	DeleteFontToHandle(fontHandle2_);

}
