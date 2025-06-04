#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "AnimControl.h"


// アニメーションの初期化処理
void AnimControl::Init(int modelHandle)
{
    modelId_ = modelHandle;              // モデルIDを保存
    currentAnim_ = ANIM_MAX;             // 再生中アニメなし（無効値で初期化）
    step_ = 0.0f;                        // 時間もリセット

    // 各アニメーションをモデルにアタッチしておく
    for (int i = 0; i < ANIM_MAX; i++) 
    {
        attachNo_[i] = MV1AttachAnim(modelId_, i);                     // モデルにアニメをアタッチ
        MV1SetAttachAnimBlendRate(modelId_, attachNo_[i], 0.0f);      // 最初は blend rate 0（表示しない）
        totalTime_[i] = MV1GetAttachAnimTotalTime(modelId_, attachNo_[i]); // アニメの長さを取得
		animSpeed_[i] = 1.0f; // 各アニメの再生速度を初期化     
    }

	totalTime_[ANIM_ATTACK] = totalTime_[ANIM_ATTACK] * ATTACK_ANIM_TIME; // 攻撃アニメの長さを調整

    isAttack_ = false; // 攻撃中フラグ初期化

    Play(ANIM_IDLE, 1); // 最初は待機アニメーションを再生

	// ブレンドの初期化
	blendTime_ = 0.5f; // ブレンドにかける時間（秒）
	blendTimer_ = 0.0f; // ブレンド中の経過時間
	isBlending_ = false; // ブレンド中フラグ初期化
	prevAnim_ = ANIM_MAX; // 前のアニメーションを無効値で初期化
}

// アニメーション再生
void AnimControl::Play(ANIM_TYPE animType, float speed) 
{
    // 攻撃中はアニメーションを切り替えない
    if (isAttack_ && animType != ANIM_ATTACK) return;

    // 同じアニメを再生しようとしてたら何もしない
    if ( animType == currentAnim_ )
    {
        // 速度だけ更新（再生位置やブレンドはしない）
        animSpeed_[animType] = speed;
        return;
    }

    // ブレンド準備：切り替え前の currentAnim_ を prevAnim_ に保存
    prevAnim_ = currentAnim_;

    // 前のアニメを非表示にする（blend rate を 0）
    if (currentAnim_ != ANIM_MAX)
    {
        MV1SetAttachAnimBlendRate(modelId_, attachNo_[currentAnim_], 0.0f);
    }

    // 新しいアニメを再生する準備
    // 新しいアニメに切り替えるとき：再生速度も初期化
    currentAnim_ = animType;    // 新しいアニメに切り替え（step_は維持）
	step_ = 0.0f;               // 毎回最初から再生
	animSpeed_[animType] = speed; // アニメの再生速度を設定
    
    // ブレンド準備
    blendTimer_ = 0.0f;
    isBlending_ = true;

    // 前アニメが存在していれば、その表示を100%に
	if (prevAnim_ != ANIM_MAX)
	{
		MV1SetAttachAnimBlendRate(modelId_, attachNo_[prevAnim_], 1.0f);
	}

    // 再生位置設定
	MV1SetAttachAnimTime(modelId_, attachNo_[currentAnim_], step_);     // 再生位置を設定

    // 攻撃開始したらフラグを立てる
    if (animType == ANIM_ATTACK) { isAttack_ = true; }

}

// フレームごとにアニメーションを進める処理
void AnimControl::Update()
{
    // 毎フレームの経過時間
    float baseDt = 1;
	float animDt = baseDt * animSpeed_[currentAnim_]; // アニメの再生速度を計算
    // アニメの再生を進める
    step_ += animDt;


    // アニメの再生時間が終了したら
    if (step_ > totalTime_[currentAnim_])
    {
        // 死亡以外のアニメはループする
        if (currentAnim_ != ANIM_DIE)
        {
            step_ = 0.0f; // 通常アニメはループ
        }
        // 攻撃アニメだった場合
        if (currentAnim_ == ANIM_ATTACK)
        {
            // 攻撃アニメ終了 → 待機に戻す
            isAttack_ = false;
      
        }
    }

    // アニメの再生位置をモデルに設定
    MV1SetAttachAnimTime(modelId_, attachNo_[currentAnim_], step_);

	// ブレンド処理
    if (isBlending_)
    {
        float blendDt = SceneManager::GetInstance()->GetDeltaTime();;
        blendTimer_ += blendDt;
        float rate = blendTimer_ / blendTime_;

        if (rate >= 1.0f)
        {
            // Blend 完了
            rate = 1.0f;
            isBlending_ = false;

            // 前アニメを完全に切る
            if (prevAnim_ != ANIM_MAX)
            {
                MV1SetAttachAnimBlendRate(modelId_, attachNo_[prevAnim_], 0.0f);
                prevAnim_ = ANIM_MAX;
            }
        }

        // Blend率を適用
        if (prevAnim_ != ANIM_MAX)
        {
            // 前アニメの表示を減らす
            MV1SetAttachAnimBlendRate(modelId_, attachNo_[prevAnim_], 1.0f - rate);
        }
        // 新アニメの表示を増やす
        MV1SetAttachAnimBlendRate(modelId_, attachNo_[currentAnim_], rate);
    }
}

void AnimControl::Draw()
{
}

// アニメーションの後片付け（Detach）
void AnimControl::Release() 
{
    // 全アニメをモデルから外す
    for (int i = 0; i < ANIM_MAX; i++)
    {
        MV1DetachAnim(modelId_, attachNo_[i]);
    }
}

float AnimControl::GetCurrentAnimRate() const
{
    // 現在のアニメの再生割合を返す（0.0～1.0）
    if (totalTime_[currentAnim_] == 0.0f) return 0.0f;
    return step_ / totalTime_[currentAnim_];
}
