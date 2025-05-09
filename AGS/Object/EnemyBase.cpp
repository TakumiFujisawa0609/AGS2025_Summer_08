#include <DxLib.h>
#include "EnemyBase.h"

void EnemyBase::Init()
{
	// 敵モデル描画
	idleModelId_ = MV1LoadModel("Data/Model/Enemy/Walk.mv1");

	// 敵初期位置
	enemyPos_ = INIT_ENEMY_POS;
	// 敵初期角度
	enemyAngle_ = INIT_ENEMY_ANGLE;

	// 敵モデルを敵座標にセット
	MV1SetPosition(idleModelId_, enemyPos_);

	// アニメーションのセットアップ
	int animIndex = 5;  // 5番のアニメーション開始
	attachAnimIndex_ = MV1AttachAnim(idleModelId_, animIndex); // モデルにアニメーションセット
	MV1SetAttachAnimBlendRate(idleModelId_, attachAnimIndex_, 1.0f); // 

	animTime_ = 0.0f;	// 初期アニメーション再生時間
	animTotalTime_ = MV1GetAttachAnimTotalTime(idleModelId_, attachAnimIndex_); // アニメーション最大時間
}

void EnemyBase::Update()
{
	// アニメーションを進める
	animTime_ += 1.0f;  // 毎フレーム 1 秒進める

	// アニメーションの最大再生時間を超えたら
	if (animTime_ >= animTotalTime_)
	{
		animTime_ = 0.0f;  // 最初に戻す（ループ）
	}
	// アニメーション更新
	MV1SetAttachAnimTime(idleModelId_, attachAnimIndex_, animTime_);
	
}

void EnemyBase::Draw()
{
	// 敵モデル描画
	MV1DrawModel(idleModelId_);

	// デバッグ
	DrawFormatString(0, 20, 0xffffff, "enemyPos : (%f, %f, %f)", enemyPos_.x, enemyPos_.y, enemyPos_.z);
}

void EnemyBase::Release()
{
	// 敵モデル開放
	MV1DeleteModel(idleModelId_);
}