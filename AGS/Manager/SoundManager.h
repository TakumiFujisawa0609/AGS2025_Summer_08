#pragma once
#include <DxLib.h>

#define WALK_PATH "Data/Sound/walk.wav"
#define OPEN_PATH "Data/Sound/open.wav"
#define CLOSE_PATH "Data/Sound/close.wav"
#define DIE_PATH "Data/Sound/die.wav"
#define NOBULLET_PATH "Data/Sound/noBullet.wav"
#define RELOAD_PATH "Data/Sound/reLoad.wav"
#define SHOT_PATH "Data/Sound/shot.wav"
#define PICKUP_PATH "Data/Sound/pickUp.wav"
#define VOICE_PATH "Data/Sound/voice.wav"

class SoundManager
{
public:

	static constexpr int BGM_VOLUME = 255;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int WALK_VOLUME = 255;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int OPEN_VOLUME = 255;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int CLOSE_VOLUME = 255;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int DIE_VOLUME = 255;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int NOBULLET_VOLUME = 255;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int RELOAD_VOLUME = 255;		// BGM‚Ì‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int SHOT_VOLUME = 255;	// •à‚­‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int PICKUP_VOLUME = 255;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj
	static constexpr int VOICE_VOLUME = 255;		// ‘–‚é‰¹—Êi‚O`‚Q‚T‚Tj


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
	//void PlayBgm1();	// BGM
	void PlayWalk();	// •à‚­
	void PlayOpen();	// ‘–‚é
	void PlayClose();	// •à‚­
	void PlayDie();	// ‘–‚é
	void PlayNoAmmo();	// •à‚­
	void PlayPickUp();	// ‘–‚é
	void PlayReLoad();	// •à‚­
	void PlayVoice();	// ‘–‚é
	void PlayShot();	// •à‚­

	
	//‰¹Œ¹’â~
	void StopBgm1();	// BGM
	void StopWalk1();	// •à‚­
	void StopOpen();	// ‘–‚é
	void StopClose();	// •à‚­
	void StopDie();	// ‘–‚é
	void StopNoAmmo();	// •à‚­
	void StopPickUp();	// ‘–‚é
	void StopReLoad();	// •à‚­
	void StopVoice();	// ‘–‚é
	void StopShot();	// ‘–‚é

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
	int dieHundle_;
	int noAmmoHundle_;
	int pickUpHundle_;
	int reLoadHundle_;
	int voiceHundle_;
	int shotHundle_;

};


