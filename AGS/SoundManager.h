#pragma once
#include <DxLib.h>

#define BGM1_PATH "Data/BGM1.mp3"
#define RUN1_PATH "Data/Run1.wav"
#define JUMP1_PATH "Data/Jump1.wav"
#define LANDING1_PATH "Data/Landing1.wav"

class SoundManager
{
public:

	static constexpr int BGM1_VOLUME = 130;		// BGMの音量（０～２５５）
	static constexpr int RUN1_VOLUME = 125;		// 走る音量（０～２５５）
	static constexpr int JUMP1_VOLUME = 90;		// ジャンプの音量（０～２５５）
	static constexpr int LANDING1_VOLUME = 125;	// 着地の音量（０～２５５）

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
	void PlayRun1();	// 走る
	void PlayJump1();	// ジャンプ
	void PlayLanding1();// 着地
	//音源停止
	void StopBgm1();	//BGM
	void StopRun1();	//走る


private:

	//コンストラクタ・デストラクタ（外部からの生成防止）
	SoundManager(void);
	~SoundManager(void);
	//コピーコンストラクタ
	SoundManager(const SoundManager& sound);

	// インスタンスを持たせる
	static SoundManager* instance_;

	int bgm1Hundle_;
	int run1Hundle_;
	int landing1Hundle_;
	int jump1Hundle_;
};


