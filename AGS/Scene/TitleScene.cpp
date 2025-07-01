#include <DxLib.h>
#include "../Manager/Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Object/Camera.h"
#include "TitleScene.h"
#include "../Object/Button/Button.h"
#include "../Object/Button/ExitButton.h"


TitleScene::TitleScene(void)
{
	button_ = nullptr;
	
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init()
{	

	mousePos_X = Application::SCREEN_SIZE_X / 2;
	mousePos_Y = Application::SCREEN_SIZE_Y / 2;
	
	
	SetMouseDispFlag(true);
	SetMousePoint(mousePos_X, mousePos_Y);


	camera_ = new Camera();
	testTitleImg_ = LoadGraph("Data/Image/ReTitle.png");

	button_ = new Button(500,900,500,200);
	button_->Init();

	exitButton_ = new ExitButton(1400, 900, 500, 200);
	exitButton_->Init();

	frameImage_ = LoadGraph("Data/Image/Frame.png");
	
}

void TitleScene::Update(void)
{
	// 毎フレーム呼ばれる処理内で

	GetMousePoint(&mousePos_X, &mousePos_Y);

	//ボタン更新
	button_->Update();
	//ボタン更新
	exitButton_->Update();


	if (button_->GetButtonState() == Button::BUTTON_STATE::DISABLED)
	{
		//チュートリアルシーン遷移
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::T);
		SoundManager::GetInstance()->PlayOpen();
	}

	if (exitButton_->GetButtonState() == ExitButton::BUTTON_STATE::DISABLED)
	{
		SceneManager::GetInstance()->SetGameEnd();
	}

}

void TitleScene::Draw(void)
{
	// test背景
	float scale = 1.1f;  // 縮小
	DrawRotaGraph(958, 538, scale, 0.0f, testTitleImg_, true);

	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, testTitleImg_, true);


	button_->Draw();
	exitButton_->Draw();
	
}

void TitleScene::Release(void)
{
	button_->Release();
	exitButton_->Release();

	DeleteGraph(testTitleImg_);
}