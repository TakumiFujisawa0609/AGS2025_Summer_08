#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Common/AnimControl.h"
#include "EnemyNormal.h"

EnemyNormal::EnemyNormal(void)
{
}

EnemyNormal::~EnemyNormal(void)
{
}

void EnemyNormal::ChangeWalk(void)
{
	//アニメ再生
	anim_->Play(ANIM_WALK, 1);

	speed_ = MOVE_WALK_SPEED;  // 歩き速度

	// 再生済みでなければ再生
	if (!hasPlayedRunSound_)
	{
		SoundManager::GetInstance()->PlayVoice(pos_);
		hasPlayedRunSound_ = true;
	}
}

void EnemyNormal::ChangeDie()
{
	// アニメ再生
	anim_->Play(ANIM_DIE, 1);

	speed_ = 0.0f;

	// 死亡時の処理
	SoundManager::GetInstance()->StopVoice();
	SoundManager::GetInstance()->PlayKill();

	// キルカウント加算
	SceneManager::GetInstance()->SetKillEnemyCnt(1);
}

void EnemyNormal::SetParam()
{
	// ダメージを受ける
	hp_ = 3;

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
