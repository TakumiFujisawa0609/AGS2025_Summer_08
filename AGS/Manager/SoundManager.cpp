#include "SoundManager.h"
#include "InputManager.h"
#include "DxLib.h"

// グローバル領域で変数を初期化
SoundManager* SoundManager::instance_ = nullptr;


SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
}


SoundManager::SoundManager(const SoundManager& sound)
{
}

//インスタンスの生成
void SoundManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SoundManager;
	}
}

//インスタンスの取得
SoundManager* SoundManager::GetInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SoundManager;
	}
	return instance_;
}

// インスタンス削除
void SoundManager::DeleteInstance(void)
{
	if (instance_ != nullptr)
	{
		delete instance_;
	}
}

void SoundManager::Init(void)
{
	// BGM読み込み
	bgm1Hundle_ = LoadSoundMem(BGM1_PATH);

	// 走る音読み込み
	run1Hundle_ = LoadSoundMem(RUN1_PATH);

}

void SoundManager::Update(void)
{
	PlayBgm1();
	PlayRun1();
}

void SoundManager::Release(void)
{
	DeleteSoundMem(bgm1Hundle_);
	DeleteSoundMem(run1Hundle_);

	// インスタンスの削除
	DeleteInstance();
}

// BGM１再生
void SoundManager::PlayBgm1()
{
	// 再生
	if (CheckSoundMem(bgm1Hundle_) == 0)
	{
		PlaySoundMem(bgm1Hundle_, DX_PLAYTYPE_LOOP, true);
	}

	// 音量調整
	ChangeVolumeSoundMem(BGM1_VOLUME, bgm1Hundle_);
}

// 走る音
void SoundManager::PlayRun1()
{
	// 再生
	PlaySoundMem(run1Hundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(RUN1_VOLUME, run1Hundle_);
}

// BGM１停止
void SoundManager::StopBgm1()
{
	StopSoundMem(bgm1Hundle_);
}

// 走る１停止
void SoundManager::StopRun1()
{
	StopSoundMem(run1Hundle_);
}
