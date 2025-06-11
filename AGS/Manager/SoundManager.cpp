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
	//bgm1Hundle_ = LoadSoundMem(BGM1_PATH);

	walkHundle_ = LoadSoundMem(WALK_PATH);
	openHundle_ = LoadSoundMem(OPEN_PATH);
	closeHundle_ = LoadSoundMem(CLOSE_PATH);
	dieHundle_ = LoadSoundMem(DIE_PATH);
	noAmmoHundle_ = LoadSoundMem(NOBULLET_PATH);
	pickUpHundle_ = LoadSoundMem(PICKUP_PATH);
	reLoadHundle_ = LoadSoundMem(RELOAD_PATH);
	voiceHundle_ = LoadSoundMem(VOICE_PATH);
	shotHundle_ = LoadSoundMem(SHOT_PATH);
}

void SoundManager::Update(void)
{
	//PlayBgm1();
	PlayWalk();
}

void SoundManager::Release(void)
{
	//DeleteSoundMem(bgmHundle_);
	DeleteSoundMem(walkHundle_);


	// インスタンスの削除
	DeleteInstance();
}

//// BGM１再生
//void SoundManager::PlayBgm1()
//{
//	// 再生
//	if (CheckSoundMem(bgm1Hundle_) == 0)
//	{
//		PlaySoundMem(bgm1Hundle_, DX_PLAYTYPE_LOOP, true);
//	}
//
//	// 音量調整
//	ChangeVolumeSoundMem(BGM1_VOLUME, bgm1Hundle_);
//}

void SoundManager::PlayWalk()
{
	// 再生
	if (CheckSoundMem(walkHundle_) == 0)
	{
		// 再生
		PlaySoundMem(walkHundle_, DX_PLAYTYPE_BACK, true);
	}
	

	// 音量調整
	ChangeVolumeSoundMem(WALK_VOLUME, walkHundle_);
}

void SoundManager::PlayOpen()
{
	// 再生
	PlaySoundMem(openHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(OPEN_VOLUME, openHundle_);
}

void SoundManager::PlayClose()
{
	// 再生
	PlaySoundMem(closeHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(CLOSE_VOLUME, closeHundle_);
}

void SoundManager::PlayDie()
{
	// 再生
	PlaySoundMem(dieHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(DIE_VOLUME, dieHundle_);
}

void SoundManager::PlayNoAmmo()
{
	// 再生
	PlaySoundMem(noAmmoHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(NOBULLET_VOLUME, noAmmoHundle_);
}

void SoundManager::PlayPickUp()
{
	// 再生
	PlaySoundMem(pickUpHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(PICKUP_VOLUME, pickUpHundle_);
}

void SoundManager::PlayReLoad()
{
	// 再生
	PlaySoundMem(reLoadHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(RELOAD_VOLUME, reLoadHundle_);
}

void SoundManager::PlayVoice()
{
	// 再生
	PlaySoundMem(voiceHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(VOICE_VOLUME, voiceHundle_);
}

void SoundManager::PlayShot()
{
	// 再生
	PlaySoundMem(shotHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(SHOT_VOLUME, shotHundle_);
}

//// 走る音
//void SoundManager::PlayRun1()
//{
//	// 再生
//	PlaySoundMem(run1Hundle_, DX_PLAYTYPE_BACK, true);
//
//	// 音量調整
//	ChangeVolumeSoundMem(RUN1_VOLUME, run1Hundle_);
//}

// BGM１停止
void SoundManager::StopBgm1()
{
	StopSoundMem(bgm1Hundle_);
}

void SoundManager::StopWalk()
{
	StopSoundMem(walkHundle_);
}

void SoundManager::StopOpen()
{
}

void SoundManager::StopClose()
{
}

void SoundManager::StopDie()
{
}

void SoundManager::StopNoAmmo()
{
}

void SoundManager::StopPickUp()
{
}

void SoundManager::StopReLoad()
{
}

void SoundManager::StopVoice()
{
}

void SoundManager::StopShot()
{
}