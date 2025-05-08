#pragma once
#include <DxLib.h>

#define BGM1_PATH "Data/BGM1.mp3"
#define WALK1_PATH "Data/WALK1.wav"
#define RUN1_PATH "Data/Run1.wav"
<<<<<<< HEAD

=======
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70

class SoundManager
{
public:

	static constexpr int BGM1_VOLUME = 130;		// BGMの音量（０～２５５）
<<<<<<< HEAD
	static constexpr int WALK1_VOLUME = 125;	// 歩く音量（０～２５５）
	static constexpr int RUN1_VOLUME = 125;		// 走る音量（０～２５５）

=======
	static constexpr int RUN1_VOLUME = 125;		// 走る音量（０～２５５)
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70

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
	void PlayBgm1();	// BGM
	void PlayWalk();	// 歩く
	void PlayRun1();	// 走る
<<<<<<< HEAD
	
=======
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
	//音源停止
	void StopBgm1();	// BGM
	void StopWalk1();	// 歩く
	void StopRun1();	// 走る


private:

	//コンストラクタ・デストラクタ（外部からの生成防止）
	SoundManager(void);
	~SoundManager(void);
	//コピーコンストラクタ
	SoundManager(const SoundManager& sound);

	// インスタンスを持たせる
	static SoundManager* instance_;

	int bgm1Hundle_;
	int walk1Hundle_;
	int run1Hundle_;
<<<<<<< HEAD

=======
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
};


