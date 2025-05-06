#include <DxLib.h>
#include "../Scene/GameScene.h"
#include "EnemyBase.h"
#include "Camera.h"



void EnemyBase::Init(GameScene* gameScene, Camera* camera)
{
	gameScene_ = gameScene; // GameSceneのインスタンスを取得
	camera_ = camera;		// GameScene内カメラのインスタンスを取得

	// 敵モデル読み込み
	enemyModelId_ = MV1LoadModel("Data/Model/Enemy/Zombie_Idle.mv1");
	// 敵座標設定
	enemyPos_ = INIT_ENEMY_POS;
	// 敵の大きさ設定
	enemyScale_ = INIT_ENEMY_SCALE;

	// 敵の生存判定
	isAliveEnemy_ = false;

	// 敵の座標をモデルに設定
	MV1SetPosition(enemyModelId_, enemyPos_);
	// 敵の大きさ設定
	MV1SetScale(enemyModelId_, enemyScale_);
	// 敵の向き設定
	//MV1SetRotationXYZ(enemyModelId_, { 0.0f, 180.f * DX_PI_F / 180.0f, 0.0f });

	// アニメーションをアタッチ
	animIndex_ = MV1AttachAnim(enemyModelId_, 0);
}

void EnemyBase::Update(void)
{
	// アニメーション時間を自動で１フレームずつ進行（再生）
	MV1SetAttachAnimTime(enemyModelId_, animIndex_, MV1GetAttachAnimTime(enemyModelId_, animIndex_) + 1.0f);

	// アニメーションが終わったらループさせる
	float animTotalTime = MV1GetAnimTotalTime(enemyModelId_, animIndex_);
	if (MV1GetAttachAnimTime(enemyModelId_, animIndex_) >= animTotalTime)
	{
		MV1SetAttachAnimTime(enemyModelId_, animIndex_, 0.0f);
	}

}

void EnemyBase::Draw(void)
{
	// 
	MV1DrawModel(enemyModelId_);
}



void EnemyBase::Release(void)
{
	// 敵モデルの開放
	MV1DeleteModel(enemyModelId_);

}

VECTOR EnemyBase::GetEnemyPos(void)
{
	return enemyPos_;
}

void EnemyBase::SetIsAliveEnemy(bool isAliveEnemy)
{
	isAliveEnemy_ = isAliveEnemy;
}

bool EnemyBase::GetIsAliveEnemy(void)
{
	return isAliveEnemy_;
}


