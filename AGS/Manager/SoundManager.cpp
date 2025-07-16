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
	//SetCreate3DSoundFlag(TRUE);
	//SetEnableXAudioFlag(TRUE);
	voiceHundle_ = LoadSoundMem(VOICE_PATH);
	fVoiceHundle_ = LoadSoundMem(FVOICE_PATH);
	pVoiceHundle_ = LoadSoundMem(PVOICE_PATH);
	//SetCreate3DSoundFlag(FALSE);

	// BGM読み込み
	bgm1Hundle_ = LoadSoundMem(BGM1_PATH);
	bgm2Hundle_ = LoadSoundMem(BGM2_PATH);
	bgm3Hundle_ = LoadSoundMem(BGM3_PATH);
	clearHundle_ = LoadSoundMem(CLEAR_PATH);
	walkHundle_ = LoadSoundMem(WALK_PATH);
	openHundle_ = LoadSoundMem(OPEN_PATH);
	closeHundle_ = LoadSoundMem(CLOSE_PATH);
	hitHundle_ = LoadSoundMem(HIT_PATH);
	dieHundle_ = LoadSoundMem(DIE_PATH);
	fDieHundle_ = LoadSoundMem(FDIE_PATH);
	pDieHundle_ = LoadSoundMem(PDIE_PATH);
	noAmmoHundle_ = LoadSoundMem(NOBULLET_PATH);
	pickUpHundle_ = LoadSoundMem(PICKUP_PATH);
	reLoadHundle_ = LoadSoundMem(RELOAD_PATH);
	shotHundle_ = LoadSoundMem(SHOT_PATH);
	hoverHundle_ = LoadSoundMem(HOVER_PATH);
	cleckHundle_ = LoadSoundMem(CLECK_PATH);
	choiceHundle_ = LoadSoundMem(CHOICE_PATH);
	pauseHundle_ = LoadSoundMem(PAUSE_PATH);
	impactHundle_ = LoadSoundMem(IMPACT_PATH);
	healHundle_ = LoadSoundMem(HEAL_PATH);
	healVoiceHundle_ = LoadSoundMem(HEALVOICE_PATH);
	damageHundle_= LoadSoundMem(DAMEGE_PATH);
	countHundle_ = LoadSoundMem(COUNT_PATH);
	killHundle_ = LoadSoundMem(KILL_PATH);
	order1Hundle_ = LoadSoundMem(ORDERL1_PATH);
	order2Hundle_ = LoadSoundMem(ORDERL2_PATH);
	order3Hundle_ = LoadSoundMem(ORDERL3_PATH);
	paperHundle_ = LoadSoundMem(PAPER_PATH);

	isDamegeEnd_ = true;
}

void SoundManager::Update(void)
{
	//PlayBgm1();
	PlayWalk();
}

void SoundManager::Release(void)
{
	DeleteSoundMem(bgm1Hundle_);
	DeleteSoundMem(bgm2Hundle_);
	DeleteSoundMem(bgm3Hundle_);
	DeleteSoundMem(walkHundle_);
	DeleteSoundMem(openHundle_);
	DeleteSoundMem(closeHundle_);
	DeleteSoundMem(hitHundle_);
	DeleteSoundMem(dieHundle_);
	DeleteSoundMem(fDieHundle_);
	DeleteSoundMem(pDieHundle_);
	DeleteSoundMem(noAmmoHundle_);
	DeleteSoundMem(pickUpHundle_);
	DeleteSoundMem(reLoadHundle_);
	DeleteSoundMem(voiceHundle_);
	DeleteSoundMem(fVoiceHundle_);
	DeleteSoundMem(pVoiceHundle_);
	DeleteSoundMem(shotHundle_);
	DeleteSoundMem(hoverHundle_);
	DeleteSoundMem(cleckHundle_);
	DeleteSoundMem(choiceHundle_);
	DeleteSoundMem(pauseHundle_);
	DeleteSoundMem(impactHundle_);
	DeleteSoundMem(healHundle_);
	DeleteSoundMem(healVoiceHundle_);
	DeleteSoundMem(damageHundle_);
	DeleteSoundMem(countHundle_);
	DeleteSoundMem(killHundle_);
	DeleteSoundMem(order1Hundle_);
	DeleteSoundMem(order2Hundle_);
	DeleteSoundMem(order3Hundle_);
	DeleteSoundMem(clearHundle_);
	DeleteSoundMem(paperHundle_);

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

// タイトル
void SoundManager::PlayBgm2()
{
	// 再生
	if (CheckSoundMem(bgm2Hundle_) == 0)
	{
		PlaySoundMem(bgm2Hundle_, DX_PLAYTYPE_LOOP, true);
	}

	// 音量調整
	ChangeVolumeSoundMem(BGM2_VOLUME, bgm2Hundle_);
}

void SoundManager::PlayClear()
{
	// 再生
	if (CheckSoundMem(clearHundle_) == 0)
	{
		PlaySoundMem(clearHundle_, DX_PLAYTYPE_LOOP, true);
	}

	// 音量調整
	ChangeVolumeSoundMem(CLEAR_VOLUME, clearHundle_);
}

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

void SoundManager::PlayHit()
{
	// 再生
	PlaySoundMem(hitHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(HIT_VOLUME, hitHundle_);
}

void SoundManager::PlayDie()
{
	// 再生
	PlaySoundMem(dieHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(DIE_VOLUME, dieHundle_);
}

void SoundManager::PlayFDie()
{
	// 再生
	if (CheckSoundMem(fDieHundle_) == 0)
	{
		// 再生
		PlaySoundMem(fDieHundle_, DX_PLAYTYPE_BACK, true);
	}
	// 音量調整
	ChangeVolumeSoundMem(FDIE_VOLUME, fDieHundle_);
}

void SoundManager::PlayPDie()
{
	// 再生
	if (CheckSoundMem(pDieHundle_) == 0)
	{
		// 再生
		PlaySoundMem(pDieHundle_, DX_PLAYTYPE_BACK, true);
	}
	// 音量調整
	ChangeVolumeSoundMem(PDIE_VOLUME, pDieHundle_);
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

void SoundManager::PlayVoice(VECTOR pos)
{
	// 再生
	if (CheckSoundMem(voiceHundle_) == 0)
	{
		// 再生
		PlaySoundMem(voiceHundle_, DX_PLAYTYPE_BACK, true);
	}

	// 敵の位置を3D音源に設定
	//Set3DPositionSoundMem(pos, voiceHundle_);
	//Set3DRadiusSoundMem(1830.0f, voiceHundle_);

	//Set3DDistanceFactor(0.5f);

	// 音量調整
	ChangeVolumeSoundMem(VOICE_VOLUME, voiceHundle_);
}

void SoundManager::PlayFVoice()
{
	// 再生
	if (CheckSoundMem(fVoiceHundle_) == 0)
	{
		// 再生
		PlaySoundMem(fVoiceHundle_, DX_PLAYTYPE_BACK, true);
	}
	// 音量調整
	ChangeVolumeSoundMem(FVOICE_VOLUME, voiceHundle_);
}

void SoundManager::PlayPVoice()
{
	// 再生
	if (CheckSoundMem(pVoiceHundle_) == 0)
	{
		// 再生
		PlaySoundMem(pVoiceHundle_, DX_PLAYTYPE_BACK, true);
	}
	// 音量調整
	ChangeVolumeSoundMem(PVOICE_VOLUME, pVoiceHundle_);
}

void SoundManager::PlayShot()
{
	// 再生
	PlaySoundMem(shotHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(SHOT_VOLUME, shotHundle_);
}

void SoundManager::PlayCleck()
{
	// 再生
	PlaySoundMem(cleckHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(CLECK_VOLUME, cleckHundle_);
}

void SoundManager::PlayChoice()
{
	// 再生
	PlaySoundMem(choiceHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(Choice_VOLUME, choiceHundle_);
}

void SoundManager::PlayHover()
{
	// 再生
	PlaySoundMem(hoverHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(HOVER_VOLUME, hoverHundle_);
}

void SoundManager::PlayPause()
{
	// 再生
	PlaySoundMem(pauseHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(PAUSE_VOLUME, pauseHundle_);
}

void SoundManager::PlayImpact()
{
	// 再生
	PlaySoundMem(impactHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(IMPACT_VOLUME, impactHundle_);
}


void SoundManager::PlayHeal()
{
	// 再生
	if (CheckSoundMem(healHundle_) == 0)
	{
		// 再生
		PlaySoundMem(healHundle_, DX_PLAYTYPE_BACK, true);
	}

	// 音量調整
	ChangeVolumeSoundMem(HEAL_VOLUME, cleckHundle_);
}

void SoundManager::PlayHealVoice()
{
	// 再生
	PlaySoundMem(healVoiceHundle_, DX_PLAYTYPE_BACK, true);

	// 音量調整
	ChangeVolumeSoundMem(HEALVOICE_VOLUME, cleckHundle_);
}

void SoundManager::PlayDamage()
{
	if (CheckSoundMem(damageHundle_) == 0)
	{
		// 再生
		PlaySoundMem(damageHundle_, DX_PLAYTYPE_LOOP, true);
	}

	// 音量調整
	ChangeVolumeSoundMem(DAMEGE_VOLUME, damageHundle_);
}

void SoundManager::PlayCount()
{
	if (CheckSoundMem(countHundle_) == 0)
	{
		// 再生
		PlaySoundMem(countHundle_, DX_PLAYTYPE_BACK, true);
	}
	// 音量調整
	ChangeVolumeSoundMem(COUNT_VOLUME, countHundle_);
	
}

void SoundManager::PlayKill()
{
	// 再生
	PlaySoundMem(killHundle_, DX_PLAYTYPE_BACK, true);
	// 音量調整
	ChangeVolumeSoundMem(KILL_VOLUME, killHundle_);
}

void SoundManager::PlayOrder1()
{
	// 再生
	PlaySoundMem(order1Hundle_, DX_PLAYTYPE_BACK, true);
	// 音量調整
	ChangeVolumeSoundMem(ORDER_VOLUME, order1Hundle_);
}

void SoundManager::PlayOrder2()
{
	// 再生
	PlaySoundMem(order2Hundle_, DX_PLAYTYPE_BACK, true);
	// 音量調整
	ChangeVolumeSoundMem(ORDER_VOLUME, order2Hundle_);
}

void SoundManager::PlayOrder3()
{
	// 再生
	PlaySoundMem(order3Hundle_, DX_PLAYTYPE_BACK, true);
	// 音量調整
	ChangeVolumeSoundMem(ORDER_VOLUME, order3Hundle_);
}

void SoundManager::PlayPaper()
{
	// 再生
	PlaySoundMem(paperHundle_, DX_PLAYTYPE_BACK, true);
	// 音量調整
	ChangeVolumeSoundMem(PARPER_VOLUME, paperHundle_);
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

void SoundManager::StopBgm2()
{
	StopSoundMem(bgm2Hundle_);
}

void SoundManager::StopClear()
{
	StopSoundMem(clearHundle_);
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

void SoundManager::StopFDie()
{
}

void SoundManager::StopPDie()
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
	StopSoundMem(voiceHundle_);
}

void SoundManager::StopFVoice()
{
	StopSoundMem(fVoiceHundle_);
}

void SoundManager::StopPVoice()
{
	StopSoundMem(pVoiceHundle_);
}

void SoundManager::StopShot()
{
}

void SoundManager::StopHeal()
{
	StopSoundMem(healHundle_);
}

void SoundManager::StopDamage()
{
	StopSoundMem(damageHundle_);
}

void SoundManager::StopKill()
{
}

void SoundManager::StopOrder1()
{
	StopSoundMem(order1Hundle_);
}

void SoundManager::StopOrder2()
{
	StopSoundMem(order2Hundle_);
}

void SoundManager::StopOrder3()
{
	StopSoundMem(order3Hundle_);
}

void SoundManager::StopPaper()
{
	StopSoundMem(paperHundle_);
}

bool SoundManager::IsPlayOrder1()
{
	return CheckSoundMem(order1Hundle_) == 1;
}

bool SoundManager::IsPlayOrder2()
{
	return CheckSoundMem(order2Hundle_) == 1;
}

bool SoundManager::IsPlayOrder3()
{
	return CheckSoundMem(order3Hundle_) == 1;
}

bool SoundManager::IsPlayClear()
{
	return CheckSoundMem(clearHundle_) == 1;
}


