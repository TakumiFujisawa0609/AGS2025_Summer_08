#pragma once
#include <DxLib.h>

#define WALK_PATH "Data/Sound/walk.wav"
#define OPEN_PATH "Data/Sound/open.wav"
#define CLOSE_PATH "Data/Sound/close.wav"
#define HIT_PATH "Data/Sound/hit.wav"
#define DIE_PATH "Data/Sound/die.wav"
#define FDIE_PATH "Data/Sound/FZombieDie.wav"
#define PDIE_PATH "Data/Sound/PZombieDie.wav"
#define NOBULLET_PATH "Data/Sound/noBullet.wav"
#define RELOAD_PATH "Data/Sound/reload.wav"
#define SHOT_PATH "Data/Sound/shot.wav"
#define PICKUP_PATH "Data/Sound/pickUp.wav"
#define VOICE_PATH "Data/Sound/voice.wav"
#define FVOICE_PATH "Data/Sound/FZombieVoice.wav"
#define PVOICE_PATH "Data/Sound/PZombieVoice.wav"
#define CLECK_PATH "Data/Sound/Cleck.wav"
#define CHOICE_PATH "Data/Sound/choice.wav"
#define HOVER_PATH "Data/Sound/Hover.mp3"
#define PAUSE_PATH "Data/Sound/Pause.wav"
#define IMPACT_PATH "Data/Sound/impact.wav"
#define HEAL_PATH "Data/Sound/heal.wav"
#define BGM1_PATH "Data/Sound/BGM.mp3"
#define BGM2_PATH "Data/Sound/BGM2.mp3"
#define BGM3_PATH "Data/Sound/BGM3.mp3"
#define HEALVOICE_PATH "Data/Sound/healVoice.wav"
#define DAMEGE_PATH "Data/Sound/Damege.mp3"
#define COUNT_PATH "Data/Sound/Count.wav"
#define KILL_PATH "Data/Sound/kill.wav"
#define ORDERL1_PATH "Data/Sound/order1.wav"
#define ORDERL2_PATH "Data/Sound/order2.wav"
#define ORDERL3_PATH "Data/Sound/order3.wav"
#define CLEAR_PATH "Data/Sound/clear.mp3"
#define PAPER_PATH "Data/Sound/paper.wav"

class SoundManager
{
public:

	static constexpr int BGM1_VOLUME = 153;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int BGM2_VOLUME = 250;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int BGM3_VOLUME = 220;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int WALK_VOLUME = 200;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int OPEN_VOLUME = 176;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int CLOSE_VOLUME = 170;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int Choice_VOLUME = 160;
	static constexpr int DIE_VOLUME = 172;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int FDIE_VOLUME = 200;	// €–S‚ÌƒCƒ[ƒW
	static constexpr int PDIE_VOLUME = 240;	// €–S‚ÌƒCƒ[ƒW
	static constexpr int HIT_VOLUME = 200;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int NOBULLET_VOLUME = 227;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int RELOAD_VOLUME = 202;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int SHOT_VOLUME = 182;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int PICKUP_VOLUME = 255;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int VOICE_VOLUME = 250;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int FVOICE_VOLUME = 200;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int PVOICE_VOLUME = 200;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int PAUSE_VOLUME = 230;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int CLECK_VOLUME = 130;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int HOVER_VOLUME = 130;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int HEAL_VOLUME = 247;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int HEALVOICE_VOLUME = 255;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int IMPACT_VOLUME = 252;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int COUNT_VOLUME = 100;
	static constexpr int DAMEGE_VOLUME = 200;
	static constexpr int KILL_VOLUME = 210;
	static constexpr int ORDER_VOLUME = 90;
	static constexpr int CLEAR_VOLUME = 200;
	static constexpr int PARPER_VOLUME = 220;


	// ƒCƒ“ƒXƒ^ƒ“ƒX‚Ì¶¬
	static void CreateInstance(void);
	// ƒCƒ“ƒXƒ^ƒ“ƒX‚Ìæ“¾
	static SoundManager* GetInstance(void);
	// ƒCƒ“ƒXƒ^ƒ“ƒX‚Ìíœ
	static void DeleteInstance(void);

	void Init(void);
	void Update(void);
	void Release(void);

	// ‰¹Œ¹Ä¶
	void PlayBgm1();	// BGM
	void PlayBgm2();	// BGM
	void PlayClear();	// BGM
	void PlayWalk();	// •à‚­
	void PlayOpen();	// ‘–‚é
	void PlayClose();	// •à‚­
	void PlayHit();
	void PlayDie();	// ‘–‚é
	void PlayFDie();	// •à‚­
	void PlayPDie();	// •à‚­
	void PlayNoAmmo();	// •à‚­
	void PlayPickUp();	// ‘–‚é
	void PlayReLoad();	// •à‚­
	void PlayVoice(VECTOR pos);	// ‘–‚é
	void PlayFVoice();
	void PlayPVoice();
	void PlayShot();	// •à‚­
	void PlayCleck();	// •à‚­
	void PlayChoice();
	void PlayHover();
	void PlayPause();
	void PlayImpact();	// €–S‚ÌƒCƒ[ƒW
	void PlayHeal();	// ‰ñ•œ
	void PlayHealVoice();
	void PlayDamage();
	void PlayCount();
	void PlayKill();
	void PlayOrder1();
	void PlayOrder2();
	void PlayOrder3();
	void PlayPaper();
	
	//‰¹Œ¹’â~
	void StopBgm1();	// BGM
	void StopBgm2();	// BGM
	void StopClear();	// BGM
	void StopWalk();	// •à‚­
	void StopOpen();	// ‘–‚é
	void StopClose();	// •à‚­
	void StopDie();		// ‘–‚é
	void StopFDie();	// •à‚­
	void StopPDie();	// •à‚­
	void StopNoAmmo();	// •à‚­
	void StopPickUp();	// ‘–‚é
	void StopReLoad();	// •à‚­
	void StopVoice();	// ‘–‚é
	void StopFVoice();	// ‘–‚é
	void StopPVoice();	// ‘–‚é
	void StopShot();	// ‘–‚é
	void StopHeal();	// ‘–‚é
	void StopDamage();
	void StopKill();
	void StopOrder1();
	void StopOrder2();
	void StopOrder3();
	void StopPaper();

	bool IsPlayOrder1();
	bool IsPlayOrder2();
	bool IsPlayOrder3();
	bool IsPlayClear();

private:

	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^EƒfƒXƒgƒ‰ƒNƒ^iŠO•”‚©‚ç‚Ì¶¬–h~j
	SoundManager(void);
	~SoundManager(void);
	//ƒRƒs[ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	SoundManager(const SoundManager& sound);

	// ƒCƒ“ƒXƒ^ƒ“ƒX‚ğ‚½‚¹‚é
	static SoundManager* instance_;

	int bgm1Hundle_;
	int bgm2Hundle_;
	int bgm3Hundle_;
	int walkHundle_;
	int openHundle_;
	int closeHundle_;
	int choiceHundle_;
	int hitHundle_;
	int dieHundle_;
	int fDieHundle_;
	int pDieHundle_;
	int noAmmoHundle_;
	int pickUpHundle_;
	int reLoadHundle_;
	int voiceHundle_;
	int fVoiceHundle_;
	int pVoiceHundle_;
	int shotHundle_;
	int hoverHundle_;
	int impactHundle_;
	int healHundle_;
	int healVoiceHundle_;
	int killHundle_;
	int order1Hundle_;
	int order2Hundle_;
	int order3Hundle_;
	int clearHundle_;
	int paperHundle_;

	//ƒNƒŠƒbƒN‰¹
	int cleckHundle_;
	//ƒ|[ƒYŒˆ’è‰¹
	int pauseHundle_;

	//ƒ_ƒ[ƒW‰¹ƒnƒ“ƒhƒ‹
	int damageHundle_;

	int countHundle_;
	bool isDamegeEnd_;
};