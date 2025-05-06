#include <DxLib.h>
#include "../Manager/Application.h"
#include "../Manager/SceneManager.h"
#include "TitleScene.h"


TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	testTitle_ = LoadGraph("Data/Image/testtitle.png");
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

	// 背景
	DrawGraph(0, 0, testTitle_, true);

}

void TitleScene::Release(void)
{
	DeleteGraph(testTitle_);
}