#include "DxLib.h"
#include "../Application.h"
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
	tutorialImg_ = LoadGraph("Data/Image/TutoRial.png");
}

void Tutorial::Update(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		sceneMng_.ChangeScene(SceneManager::SCENE_ID::GAME);
		SoundManager::GetInstance()->PlayChoice();
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//クリックされている
		sceneMng_.ChangeScene(SceneManager::SCENE_ID::GAME);
		SoundManager::GetInstance()->PlayChoice();
	}
}

void Tutorial::Draw(void)
{
	float scale = 1.0f;  // 縮小
	DrawRotaGraph(Application::SCREEN_SIZE_X/2, Application::SCREEN_SIZE_Y/2, scale, 0.0f, tutorialImg_, true);
}

void Tutorial::Release(void)
{
	DeleteGraph(tutorialImg_);
}
