#include <DxLib.h>
#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/Camera.h"
#include "../Common/Button.h"
#include "TitleScene.h"
#include "../Common/Button.h"


TitleScene::TitleScene(void)
{
	
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init()
{	
	// BGM再生
	SoundManager::GetInstance()->PlayBgm2();

	// マウスの座標
	mousePos_.x = Application::SCREEN_SIZE_X / 2;
	mousePos_.y = Application::SCREEN_SIZE_Y / 2;
	
	
	SetMouseDispFlag(true);
	SetMousePoint(mousePos_.x, mousePos_.y);
	
	testTitleImg_ = LoadGraph("Data/Image/ReTitle.png");

	normalGameStartImg_ = resMng_.Load(ResourceManager::SRC::NORMAL_GAMESTART).handleId_;
	normalExitImg_ = resMng_.Load(ResourceManager::SRC::NORMAL_EXIT).handleId_;
	hoverGameStartImg_ = resMng_.Load(ResourceManager::SRC::HOVER_GAMESTART).handleId_;
	hoverExitImg_ = resMng_.Load(ResourceManager::SRC::HOVER_EXIT).handleId_;

	// ボタンの生成と登録
	// スタートボタン
	Button* startBtn = new Button(500, 900,
		normalGameStartImg_, hoverGameStartImg_, normalGameStartImg_);
		
	startBtn->SetOnClick([&]() 
	{
		sceneMng_.ChangeScene(SceneManager::SCENE_ID::GAME);
	});
	// 配列に追加
	buttons_.emplace_back(startBtn);

	// ゲーム終了ボタン
	Button* exitBtn = new Button(1400, 900,
		normalExitImg_, hoverExitImg_, normalExitImg_);
	// 配列に追加
	buttons_.emplace_back(exitBtn);
}

void TitleScene::Update(void)
{
	// 毎フレーム呼ばれる処理内で
	GetMousePoint(&mousePos_.x, &mousePos_.y);

	//ボタン更新
	for (auto& btn : buttons_) {
		btn->Update();
	}

}

void TitleScene::Draw(void)
{
	// test背景
	float scale = 1.1f;  // 縮小
	DrawRotaGraph(958, 538, scale, 0.0f, testTitleImg_, true);

	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, testTitleImg_, true);

	// ボタン描画
	for (auto& btn : buttons_) {
		btn->Draw();
	}
	
}

void TitleScene::Release(void)
{
	DeleteGraph(testTitleImg_);
}