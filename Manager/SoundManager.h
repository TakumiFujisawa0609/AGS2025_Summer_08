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

	// 音量（０～２５５）
	static constexpr int BGM1_VOLUME = 153;		// BGM1
	static constexpr int BGM2_VOLUME = 250;		// BGM2
	static constexpr int BGM3_VOLUME = 220;		// BGM3
	static constexpr int WALK_VOLUME = 200;		// 歩行
	static constexpr int OPEN_VOLUME = 176;		// 開く
	static constexpr int CLOSE_VOLUME = 170;	// 選択 
	static constexpr int Choice_VOLUME = 160;   // 選択
	static constexpr int DIE_VOLUME = 172;		// ムキムキゾンビ死亡
	static constexpr int FDIE_VOLUME = 200;		// 女ゾンビ死亡
	static constexpr int PDIE_VOLUME = 240;		// 囚人ゾンビ死亡
	static constexpr int HIT_VOLUME = 200;		// 歩く音量（０～２５５）
	static constexpr int NOBULLET_VOLUME = 227;	// 弾切れ
	static constexpr int RELOAD_VOLUME = 202;	// リロード
	static constexpr int SHOT_VOLUME = 182;		// 射撃
	static constexpr int PICKUP_VOLUME = 255;	// 拾う
	static constexpr int VOICE_VOLUME = 250;	// ムキムキゾンビの声
	static constexpr int FVOICE_VOLUME = 200;	// 女ゾンビの声
	static constexpr int PVOICE_VOLUME = 200;	// 囚人ゾンビの声
	static constexpr int PAUSE_VOLUME = 230;	// ポーズ
	static constexpr int CLECK_VOLUME = 130;	// ポーズ時選択
	static constexpr int HOVER_VOLUME = 130;	// ポーズ時ボタンのホバー
	static constexpr int HEAL_VOLUME = 247;		// 回復
	static constexpr int HEALVOICE_VOLUME = 255;// 回復時の声
	static constexpr int IMPACT_VOLUME = 252;	// 死亡時演出
	static constexpr int COUNT_VOLUME = 100;	// スコア表示
	static constexpr int DAMEGE_VOLUME = 200;	// 被ダメージ
	static constexpr int KILL_VOLUME = 210;		// 死亡時効果
	static constexpr int ORDER_VOLUME = 90;		// 任務ボイス
	static constexpr int CLEAR_VOLUME = 200;	// クリアBGM
	static constexpr int PARPER_VOLUME = 220;   // 紙を捲る


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
	void PlayBgm2();	// BGM
	void PlayClear();	// BGM
	void PlayWalk();	// 歩く
	void PlayOpen();	// 走る
	void PlayClose();	// 歩く
	void PlayHit();
	void PlayDie();	// 走る
	void PlayFDie();	// 歩く
	void PlayPDie();	// 歩く
	void PlayNoAmmo();	// 歩く
	void PlayPickUp();	// 走る
	void PlayReLoad();	// 歩く
	void PlayVoice(VECTOR pos);	// 走る
	void PlayFVoice();
	void PlayPVoice();
	void PlayShot();	// 歩く
	void PlayCleck();	// 歩く
	void PlayChoice();
	void PlayHover();
	void PlayPause();
	void PlayImpact();	// 死亡時のイメージ
	void PlayHeal();	// 回復
	void PlayHealVoice();
	void PlayDamage();
	void PlayCount();
	void PlayKill();
	void PlayOrder1();
	void PlayOrder2();
	void PlayOrder3();
	void PlayPaper();
	
	//音源停止
	void StopBgm1();	// BGM
	void StopBgm2();	// BGM
	void StopClear();	// BGM
	void StopWalk();	// 歩く
	void StopOpen();	// 走る
	void StopClose();	// 歩く
	void StopDie();		// 走る
	void StopFDie();	// 歩く
	void StopPDie();	// 歩く
	void StopNoAmmo();	// 歩く
	void StopPickUp();	// 走る
	void StopReLoad();	// 歩く
	void StopVoice();	// 走る
	void StopFVoice();	// 走る
	void StopPVoice();	// 走る
	void StopShot();	// 走る
	void StopHeal();	// 走る
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

	//コンストラクタ・デストラクタ（外部からの生成防止）
	SoundManager(void);
	~SoundManager(void);
	//コピーコンストラクタ
	SoundManager(const SoundManager& sound);

	// インスタンスを持たせる
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

	//クリック音
	int cleckHundle_;
	//ポーズ決定音
	int pauseHundle_;

	//ダメージ音ハンドル
	int damageHundle_;

	int countHundle_;
	bool isDamegeEnd_;
};