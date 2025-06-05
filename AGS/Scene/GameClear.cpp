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
	gameClearImg_ = LoadGraph("Data/Image/gameclear.png");
}

void GameClear::Update(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameClear::Draw(void)
{
	float scale = 1.1f;  // 縮小
	DrawRotaGraph(958, 538, scale, 0.0f, gameClearImg_, true);
}

void GameClear::Release(void)
{
	DeleteGraph(gameClearImg_);
}
