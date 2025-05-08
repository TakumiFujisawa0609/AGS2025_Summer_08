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
<<<<<<< HEAD
	testTitleImg_ = LoadGraph("Data/Image/TestTitle.png");
=======
	testTitle_ = LoadGraph("Data/Image/testtitle.png");
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
}

void TitleScene::Update(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// ƒXƒy[ƒXƒL[‚ª‰Ÿ‰º‚³‚ê‚½‚çAƒQ[ƒ€ƒV[ƒ“‚Ö‘JˆÚ‚·‚é
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);
	}

}

void TitleScene::Draw(void)
{

<<<<<<< HEAD
	// test”wŒi
	DrawGraph(0, 0, testTitleImg_, true);
=======
	// ”wŒi
	DrawGraph(0, 0, testTitle_, true);
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70

}

void TitleScene::Release(void)
{
<<<<<<< HEAD
	DeleteGraph(testTitleImg_);
=======
	DeleteGraph(testTitle_);
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
}