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
#define CLECK_PATH "Data/Sound/Cleck.wav"
#define HOVER_PATH "Data/Sound/Hover.mp3"
#define PAUSE_PATH "Data/Sound/Pause.wav"
#define DAMEGE_PATH "Data/Sound/Damege.mp3"


class SoundManager
{
public:

	static constexpr int BGM_VOLUME = 255;		// BGMの音量（０～２５５）
	static constexpr int WALK_VOLUME = 255;	// 歩く音量（０～２５５）
	static constexpr int OPEN_VOLUME = 255;		// 走る音量（０～２５５）
	static constexpr int CLOSE_VOLUME = 255;		// BGMの音量（０～２５５）
	static constexpr int DIE_VOLUME = 255;	// 歩く音量（０～２５５）
	static constexpr int NOBULLET_VOLUME = 255;		// 走る音量（０～２５５）
	static constexpr int RELOAD_VOLUME = 255;		// BGMの音量（０～２５５）
	static constexpr int SHOT_VOLUME = 255;	// 歩く音量（０～２５５）
	static constexpr int PICKUP_VOLUME = 255;		// 走る音量（０～２５５）
	static constexpr int VOICE_VOLUME = 255;		// 走る音量（０～２５５）
	static constexpr int CLECK_VOLUME = 100;		// 走る音量（０～２５５）

	// インスタンスの生成
	static void CreateInstance(void);
	// インスタンスの取得
	static SoundManager* GetInstance(void);
	// インスタンスの削除
	static void DeleteInstance(void);

	void Init(void);
	void Update(void);
	void Release(void);

	// 音源再生
	//void PlayBgm1();	// BGM
	void PlayWalk();	// 歩く
	void PlayOpen();	// 走る
	void PlayClose();	// 歩く
	void PlayDie();	// 走る
	void PlayNoAmmo();	// 歩く
	void PlayPickUp();	// 走る
	void PlayReLoad();	// 歩く
	void PlayVoice();	// 走る
	void PlayShot();	// 歩く

	void PlayCleck();	// 歩く
	void PlayHover();
	void PlayPause();
	void PlayDamage();


	
	//音源停止
	void StopBgm1();	// BGM
	void StopWalk();	// 歩く
	void StopOpen();	// 走る
	void StopClose();	// 歩く
	void StopDie();	// 走る
	void StopNoAmmo();	// 歩く
	void StopPickUp();	// 走る
	void StopReLoad();	// 歩く
	void StopVoice();	// 走る
	void StopShot();	// 走る

	void StopDamege();

	bool GetisDamegeEnd_();

private:

	//コンストラクタ・デストラクタ（外部からの生成防止）
	SoundManager(void);
	~SoundManager(void);
	//コピーコンストラクタ
	SoundManager(const SoundManager& sound);

	// インスタンスを持たせる
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
	int hoverHundle_;

	//クリック音
	int cleckHundle_;
	//ポーズ決定音
	int pauseHundle_;
	//ダメージ音ハンドル
	int damageHundle_;

	bool isDamegeEnd_;
};