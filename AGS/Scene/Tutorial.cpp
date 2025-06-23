#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "Tutorial.h"

Tutorial::Tutorial(void)
{
}

Tutorial::~Tutorial(void)
{
}

void Tutorial::Init(void)
{
	tutorialImg_ = LoadGraph("Data/Image/Operation.png");
}

void Tutorial::Update(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);

		
	}
}

void Tutorial::Draw(void)
{
	float scale = 1.0f;  // 縮小
	DrawRotaGraph(958, 538, scale, 0.0f, tutorialImg_, true);
}

void Tutorial::Release(void)
{
	DeleteGraph(tutorialImg_);
}
