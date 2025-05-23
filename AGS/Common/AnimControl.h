#pragma once

// アニメーションの種類を enum で定義
enum ANIM_TYPE {
    ANIM_ATTACK,  // 攻撃
    ANIM_DIE,     // 死亡
    ANIM_IDLE,    // 待機
    ANIM_RUN,     // 走り
    ANIM_WALK,    // 歩き
    ANIM_MAX      // アニメの総数
};

class AnimControl {
public:

	static constexpr float ATTACK_ANIM_TIME = 1.0f; // 攻撃アニメの時間
    static constexpr float IDLE_ANIM_SPEED = 1.0f;


    void Init(int modelHandle);          // アニメ初期化（モデルを渡してセットアップ）
    void Play(ANIM_TYPE animType, float speed);       // 指定されたアニメーションを再生
    void Update();                       // 毎フレームの更新（時間を進める）
    void Draw();
    void Release();                      // メモリ解放などの後片付け

private:
    int modelId_;                // モデルのハンドルID
    ANIM_TYPE currentAnim_;      // 現在再生中のアニメーション
   int attachNo_[ANIM_MAX];      // アニメーションのアタッチ番号（アニメごとに保存）
   float animSpeed_[ANIM_MAX];   // 各アニメの再生速度
   float step_;                  // 現在の再生位置（時間）
    float totalTime_[ANIM_MAX];  // 各アニメの再生総時間

	bool isAttack_;  // 攻撃中フラグ

    float blendTime_;         // ブレンドにかける時間（秒）
    float blendTimer_;        // ブレンド中の経過時間
    bool isBlending_;         // ブレンド中かどうか
    int prevAnim_;            // 前のアニメーション
};

