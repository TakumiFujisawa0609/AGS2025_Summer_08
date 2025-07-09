#include <chrono>
#include <DxLib.h>
#include "Application.h"
#include "SoundManager.h"
#include "../Common/Fader.h"
#include "../Scene/SceneBase.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/GameClear.h"
#include "../Scene/Tutorial.h"
#include "../Scene/MovieScene.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance_ = nullptr;

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	isSceneChanging_ = false;

}

SceneManager::~SceneManager(void)
{
}

void SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager* SceneManager::GetInstance(void)
{
	return instance_;
}

void SceneManager::Init(void)
{

	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	sceneId_ = SCENE_ID::GAME;
	waitSceneId_ = SCENE_ID::NONE;

	fader_ = new Fader();
	fader_->Init();

	isSceneChanging_ = false;

	// 初期シーンの設定
	DoChangeScene(SCENE_ID::GAME);
	SoundManager::GetInstance()->PlayBgm2();

	// 3Dの初期設定
	Init3D();

	preTime_ = std::chrono::system_clock::now();  // ここで初期化
	clearTime_ = 0.0f;
	headShotCnt_ = 0;
}

void SceneManager::Update(void)
{
	//// フェード更新
	//fader_->Update();
	//if (isSceneChanging_)
	//{
	//	Fade();
	//}
	//else
	//{
	//	// 更新
	//	scene_->Update();
	//}

	//// デルタタイム
	//auto nowTime = std::chrono::system_clock::now();
	//deltaTime_ = static_cast<float>(
	//	std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	//preTime_ = nowTime;

	auto nowTime = std::chrono::system_clock::now();

	if (preTime_.time_since_epoch().count() != 0)
	{
		deltaTime_ = static_cast<float>(
			std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	}
	else
	{
		deltaTime_ = 0.0f;  // 初回は0秒経過とするなど適宜
	}
	preTime_ = nowTime;

	// フェード更新
	fader_->Update();

	if (isSceneChanging_)
	{
		Fade();
	}
	else
	{
		scene_->Update();
	}

}

void SceneManager::Draw(void)
{

	// 画面を初期化
	ClearDrawScreen();

	// 描画
	scene_->Draw();

	// 最後
	fader_->Draw();

}

void SceneManager::Destroy(void)
{
	scene_->Release();
	delete scene_;
	delete fader_;
	delete instance_;
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// フェード処理が終わってからシーンを変える場合もあるため、
	// 遷移先シーンをメンバ変数に保持
	waitSceneId_ = nextId;

	// フェードアウト(暗転)を開始する
	fader_->SetFade(Fader::STATE::FADE_OUT, GetColor(0, 0, 0));


	isSceneChanging_ = true;

}

void SceneManager::Init3D(void)
{
	// 背景色設定
	SetBackgroundColor(0,0,0);

	// Zバッファを有効にする
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// ライトの設定
	SetUseLighting(true);
	// 角度の設定
	//ChangeLightTypeDir({ -0,-0.5f,-0 });
}

// デルタタイムの取得
float SceneManager::GetDeltaTime(void) const
{
	return deltaTime_;
}

void SceneManager::SetClearTime(float clearTime)
{
	clearTime_ = clearTime;
}

float SceneManager::GetClearTime()
{
	return clearTime_;;
}

void SceneManager::StartFadeIn()
{
	fader_->SetFade(Fader::STATE::FADE_IN, GetColor(0, 0, 0));
	isSceneChanging_ = true;
}

// フェード中か
bool SceneManager::IsFading() const
{
	return fader_->GetState() != Fader::STATE::NONE && !fader_->IsEnd();
}

void SceneManager::SetHeadShot(int cnt)
{
	headShotCnt_ = cnt;
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{

	// 現在のシーンを解放
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	// シーンを変更する
	sceneId_ = sceneId;

	switch (sceneId_)
	{

	case SCENE_ID::NONE:
		waitSceneId_ = SCENE_ID::NONE;
		return;
	case SCENE_ID::TITLE:
		scene_ = new TitleScene();
		SoundManager::GetInstance()->StopOrder1();
		SoundManager::GetInstance()->StopOrder2();
		SoundManager::GetInstance()->StopOrder3();
		SoundManager::GetInstance()->StopClear();
		SoundManager::GetInstance()->StopBgm1();
		SoundManager::GetInstance()->PlayBgm2();
		break;
	case SCENE_ID::T:
		scene_ = new Tutorial();
		SoundManager::GetInstance()->StopBgm2();
		break;
	case SCENE_ID::MOVIE:
		scene_ = new MovieScene();
		SetMouseDispFlag(false);
		break;
	case SCENE_ID::GAME:
		scene_ = new GameScene();
		// フェードイン開始（黒から明るく）
		SceneManager::GetInstance()->StartFadeIn();
		SoundManager::GetInstance()->PlayBgm1();
		break;
	case SCENE_ID::GAMECLEAR:
		scene_ = new GameClear();
		SoundManager::GetInstance()->StopBgm1();
		//SoundManager::GetInstance()->StopClear();
		break;
	}

	// シーンの初期化
	scene_->Init();

	waitSceneId_ = SCENE_ID::NONE;

}

void SceneManager::Fade(void)
{
	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd())
		{
			// 暗転後、シーン変更
			DoChangeScene(waitSceneId_);
			fader_->SetFade(Fader::STATE::FADE_IN, GetColor(0,0,0));
		}
		break;
	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd())
		{
			// 明転後、シーン遷移終了
			fader_->SetFade(Fader::STATE::NONE, 0xff0000);
			isSceneChanging_ = false;
		}
		break;
	}

}
