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
	testTitleImg_ = LoadGraph("Image/TestTitle.png");
}

void TitleScene::Update(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);
	}

}

void TitleScene::Draw(void)
{

	// test背景
	DrawGraph(0, 0, testTitleImg_, true);

}

void TitleScene::Release(void)
{
	DeleteGraph(testTitleImg_);
}