#include <DxLib.h>
#include "../Manager/Application.h"
#include "../Manager/SceneManager.h"
#include "../Object/Camera.h"
#include "TitleScene.h"


TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{	
	camera_ = new Camera();
	
	
	testTitleImg_ = LoadGraph("Data/Image/Test1.png");
}

void TitleScene::Update(void)
{


	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);
	}

	//if (camera_->Getmouse_().x < 0)
	//{
	//	SetMousePoint(0,camera_->Getmouse_().y);
	//}

	//if (camera_->Getmouse_().x > Application::SCREEN_SIZE_X)
	//{
	//	SetMousePoint(Application::SCREEN_SIZE_X, camera_->Getmouse_().y);
	//}

	//if (camera_->Getmouse_().y < 0)
	//{
	//	SetMousePoint(camera_->Getmouse_().x,0);
	//}
	//if (camera_->Getmouse_().y > Application::SCREEN_SIZE_Y)
	//{
	//	SetMousePoint(camera_->Getmouse_().x, Application::SCREEN_SIZE_Y);
	//}

}

void TitleScene::Draw(void)
{
	// test背景
	float scale = 1.1f;  // 縮小
	DrawRotaGraph(958, 538, scale, 0.0f, testTitleImg_, true);

	SetFontSize(30);
	DrawString(0, 0, "※難易度選択は未実装→今はSPACEでゲームシーンへ", 0xffffff);
}

void TitleScene::Release(void)
{
	DeleteGraph(testTitleImg_);
}