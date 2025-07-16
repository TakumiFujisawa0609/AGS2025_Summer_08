#include <DxLib.h>
#include "../Player.h"
#include "../../Common/AnimControl.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/SceneManager.h"
#include "EnemyPrisoner.h"

EnemyPrisoner::EnemyPrisoner(void)
{
}

EnemyPrisoner::~EnemyPrisoner(void)
{
}

void EnemyPrisoner::ChangeStateDist()
{
	// プレイヤーが死んでいたら常にIDLEにする
	if (!player_->GetAlive())
	{
		ChangeState(STATE::IDLE);
		return;
	}

	// 視認できない上に到達済みならIDLEに戻る
	if (!isPlayerVisible_ && hasLastSeen_ && dist_ < RUN_DISTANCE)
	{
		hasLastSeen_ = false;
		ChangeState(STATE::IDLE);
		return;
	}

	// 状態を切り替える距離
	if (isPlayerVisible_ && dist_ < ATTACK_DISTANCE)
	{
		ChangeState(STATE::ATTACK);
	}
	//else if (dist_ < RUN_DISTANCE)
	//{
	//	ChangeState(STATE::RUN);
	//}
	else if (dist_ < WALK_DISTANCE)
	{
		ChangeState(STATE::WALK);
	}
	else if (dist_ > RUN_DISTANCE)
	{
		ChangeState(STATE::IDLE);
	}
}

void EnemyPrisoner::ChangeWalk(void)
{
	//アニメ再生
	anim_->Play(ANIM_WALK, 1);

	speed_ = 6.5f;  // 歩き速度

	// 再生済みでなければ再生
	if (!hasPPlayedRunSound_)
	{
		SoundManager::GetInstance()->PlayPVoice();
		hasPPlayedRunSound_ = true;
	}
}

void EnemyPrisoner::ChangeDie()
{
	// アニメ再生
	anim_->Play(ANIM_DIE, 1);

	speed_ = 0.0f;

	// 死亡時の処理
	SoundManager::GetInstance()->StopPVoice();
	// 死亡時の処理
	SoundManager::GetInstance()->PlayPDie();


	// キルカウント加算
	SceneManager::GetInstance()->SetKillEnemyCnt(1);
}

void EnemyPrisoner::SetParam()
{
	// ダメージを受ける
	hp_ = 2;

	MV1SetScale(modelId_, { 1, 1, 1 });

	// マテリアルをすべてエミッシブに設定
	int materialNum = MV1GetMaterialNum(modelId_);
	for (int i = 0; i < materialNum; ++i)
	{
		//MV1SetMaterialDifColor(modelId_, i, GetColorF(0.5f, 0.5f, 0.5f, 1)); // 拡散反射なし
		MV1SetMaterialSpcColor(modelId_, i, GetColorF(0.5f, 0.5f, 0.5f, 1)); // 鏡面反射なし
		MV1SetMaterialEmiColor(modelId_, i, GetColorF(0.5f, 0.5f, 0.5f, 1.0f)); // 自発光
		MV1SetMaterialAmbColor(modelId_, i, GetColorF(0.5f, 0.5f, 0.5f, 1)); // 環境光なし
	}
}
