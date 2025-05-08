#include <DxLib.h>
#include "EnemyBase.h"

void EnemyBase::Init()
{
	enemyModelId_ = MV1LoadModel("Data/Model/Enemy/idle.MV1");

	enemyPos_ = INIT_ENEMY_POS;

	MV1SetPosition(enemyModelId_, enemyPos_);
}

void EnemyBase::Update()
{
	
}

void EnemyBase::Draw()
{
	MV1DrawModel(enemyModelId_);
}

void EnemyBase::Release()
{
	MV1DeleteModel(enemyModelId_);
}
