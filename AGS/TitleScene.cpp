#include <DxLib.h>
#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"


TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	testTitle_ = LoadGraph("Image/testtitle.png");
}

void TitleScene::Update(void)
{
	if (CheckHitKey(KEY_INPUT_F1))
	{
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);
	}

}

void TitleScene::Draw(void)
{

	// 背景
	DrawGraph(0, 0, testTitle_, true);

}

void TitleScene::Release(void)
{
	DeleteGraph(testTitle_);
}