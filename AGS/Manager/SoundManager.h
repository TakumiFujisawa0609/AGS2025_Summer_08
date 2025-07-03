#pragma once
#include <DxLib.h>

#define WALK_PATH "Data/Sound/walk.wav"
#define OPEN_PATH "Data/Sound/open.wav"
#define CLOSE_PATH "Data/Sound/close.wav"
#define HIT_PATH "Data/Sound/hit.wav"
#define DIE_PATH "Data/Sound/die.wav"
#define NOBULLET_PATH "Data/Sound/noBullet.wav"
#define RELOAD_PATH "Data/Sound/reload.wav"
#define SHOT_PATH "Data/Sound/shot.wav"
#define PICKUP_PATH "Data/Sound/pickUp.wav"
#define VOICE_PATH "Data/Sound/voice.wav"
#define CLECK_PATH "Data/Sound/Cleck.wav"
#define HOVER_PATH "Data/Sound/Hover.mp3"
#define PAUSE_PATH "Data/Sound/Pause.wav"
#define IMPACT_PATH "Data/Sound/impact.wav"
#define HEAL_PATH "Data/Sound/heal.wav"
#define BGM1_PATH "Data/Sound/BGM.mp3"
#define HEALVOICE_PATH "Data/Sound/healVoice.wav"
#define DAMEGE_PATH "Data/Sound/Damege.mp3"
#define COUNT_PATH "Data/Sound/Count.wav"
#define KILL_PATH "Data/Sound/kill.wav"

class SoundManager
{
public:

	static constexpr int BGM1_VOLUME = 110;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int WALK_VOLUME = 144;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int OPEN_VOLUME = 122;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int CLOSE_VOLUME = 102;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int DIE_VOLUME = 142;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int HIT_VOLUME = 200;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int NOBULLET_VOLUME = 227;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int RELOAD_VOLUME = 232;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int SHOT_VOLUME = 182;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int PICKUP_VOLUME = 242;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int VOICE_VOLUME = 220;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int PAUSE_VOLUME = 100;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int CLECK_VOLUME = 130;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int HOVER_VOLUME = 130;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int HEAL_VOLUME = 247;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int HEALVOICE_VOLUME = 255;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int IMPACT_VOLUME = 249;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int COUNT_VOLUME = 150;
	static constexpr int DAMEGE_VOLUME = 200;
	static constexpr int KILL_VOLUME = 210;


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
	void PlayWalk();	// •à‚­
	void PlayOpen();	// ‘–‚é
	void PlayClose();	// •à‚­
	void PlayHit();
	void PlayDie();	// ‘–‚é
	void PlayNoAmmo();	// •à‚­
	void PlayPickUp();	// ‘–‚é
	void PlayReLoad();	// •à‚­
	void PlayVoice();	// ‘–‚é
	void PlayShot();	// •à‚­
	void PlayCleck();	// •à‚­
	void PlayHover();
	void PlayPause();
	void PlayImpact();	// €–S‚ÌƒCƒ[ƒW
	void PlayHeal();	// ‰ñ•œ
	void PlayHealVoice();
	void PlayDamage();
	void PlayCount();
	void PlayKill();
	
	//‰¹Œ¹’â~
	void StopBgm1();	// BGM
	void StopWalk();	// •à‚­
	void StopOpen();	// ‘–‚é
	void StopClose();	// •à‚­
	void StopDie();	// ‘–‚é
	void StopNoAmmo();	// •à‚­
	void StopPickUp();	// ‘–‚é
	void StopReLoad();	// •à‚­
	void StopVoice();	// ‘–‚é
	void StopShot();	// ‘–‚é
	void StopHeal();	// ‘–‚é
	void StopDamage();
	void StopKill();


private:

	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^EƒfƒXƒgƒ‰ƒNƒ^iŠO•”‚©‚ç‚Ì¶¬–h~j
	SoundManager(void);
	~SoundManager(void);
	//ƒRƒs[ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	SoundManager(const SoundManager& sound);

	// ƒCƒ“ƒXƒ^ƒ“ƒX‚ğ‚½‚¹‚é
	static SoundManager* instance_;

	int bgm1Hundle_;
	int walkHundle_;
	int openHundle_;
	int closeHundle_;
	int hitHundle_;
	int dieHundle_;
	int noAmmoHundle_;
	int pickUpHundle_;
	int reLoadHundle_;
	int voiceHundle_;
	int shotHundle_;
	int hoverHundle_;
	int impactHundle_;
	int healHundle_;
	int healVoiceHundle_;
	int killHundle_;

	//ƒNƒŠƒbƒN‰¹
	int cleckHundle_;
	//ƒ|[ƒYŒˆ’è‰¹
	int pauseHundle_;

	//ƒ_ƒ[ƒW‰¹ƒnƒ“ƒhƒ‹
	int damageHundle_;

	int countHundle_;
	bool isDamegeEnd_;
};