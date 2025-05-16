#include <DxLib.h>
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
    }

    Play(ANIM_IDLE); // 最初は待機アニメーションを再生
}

// アニメーション再生
void AnimControl::Play(ANIM_TYPE animType) 
{
    if (animType == currentAnim_) return; // 同じアニメを再生しようとしてたら何もしない

    // 前のアニメを非表示にする（blend rate を 0）
    if (currentAnim_ != ANIM_MAX) 
    {
        MV1SetAttachAnimBlendRate(modelId_, attachNo_[currentAnim_], 0.0f);
    }

    // 新しいアニメを再生する準備
    currentAnim_ = animType;    // 新しいアニメに切り替え（step_は維持）
    MV1SetAttachAnimBlendRate(modelId_, attachNo_[currentAnim_], 1.0f); // blend rate 1で表示
	MV1SetAttachAnimTime(modelId_, attachNo_[currentAnim_], step_);     // 再生位置を設定
}

// フレームごとにアニメーションを進める処理
void AnimControl::Update()
{
    // 毎フレームの経過時間を取得（SceneManagerは自作クラス）
    float dt = 1.0f;
    // アニメの再生を進める
    step_ += dt;

    // 死亡以外のアニメの再生が終わったら最初に戻す（ループ）
    if (currentAnim_ != ANIM_DIE && step_ > totalTime_[currentAnim_])
    {
        step_ = 0.0f;
    }

    // アニメの再生位置をモデルに設定
    MV1SetAttachAnimTime(modelId_, attachNo_[currentAnim_], step_);
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
