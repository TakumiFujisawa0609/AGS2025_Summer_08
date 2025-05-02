#include <DxLib.h>
#include "GameScene.h"
#include "EnemyBase.h"
#include "Camera.h"



void EnemyBase::Init(GameScene* gameScene, Camera* camera)
{
	gameScene_ = gameScene; // GameScene‚ÌƒCƒ“ƒXƒ^ƒ“ƒX‚ğæ“¾
	camera_ = camera;		// GameScene“àƒJƒƒ‰‚ÌƒCƒ“ƒXƒ^ƒ“ƒX‚ğæ“¾

	// “Gƒ‚ƒfƒ‹“Ç‚İ‚İ
	enemyModelId_ = MV1LoadModel("Data/Model/Enemy.mv1");
	// “GÀ•Wİ’è
	enemyPos_ = INIT_ENEMY_POS;
	// “G‚Ì‘å‚«‚³İ’è
	enemyScale_ = INIT_ENEMY_SCALE;

	// “G‚Ì¶‘¶”»’è
	isAliveEnemy_ = false;

	// “G‚ÌÀ•W‚ğƒ‚ƒfƒ‹‚Éİ’è
	MV1SetPosition(enemyModelId_, enemyPos_);
	// “G‚Ì‘å‚«‚³İ’è
	MV1SetScale(enemyModelId_, enemyScale_);
	// “G‚ÌŒü‚«İ’è
	//MV1SetRotationXYZ(enemyModelId_, { 0.0f, 180.f * DX_PI_F / 180.0f, 0.0f });



}

void EnemyBase::Update(void)
{
	// ƒQ[ƒ€ƒNƒŠƒAƒtƒ‰ƒO‚ªÜ‚ê‚Ä‚½
	if (!gameScene_->GetIsGameClear())
	{
		// “G‚ÌÄoŒ»ˆ—
		if (!isAliveEnemy_ || enemyPos_.z < camera_->GetCameraPos().z)
		{
			// ƒ‰ƒ“ƒ_ƒ€‚Ì”’l‚ğæ“¾i‚O`‚U‚O‚Oj
			int rundomNum = GetRand(600);
			//  -‚R‚O‚O`3‚O‚O‚Ì”’l‚É‚·‚é
			rundomNum -= 300;
			// “G‚ÌXÀ•W‚ğƒ‰ƒ“ƒ_ƒ€‚Éİ’è
			enemyPos_.x = rundomNum;

			// “G‚ÌÄoŒ»ZˆÊ’u‚ğİ’è
			enemyPos_.z = camera_->GetCameraPos().z + ENEMY_RESPAWN_POS_Z;
			// “G‚ÌÀ•W‚ğƒ‚ƒfƒ‹‚Éİ’è
			MV1SetPosition(enemyModelId_, enemyPos_);

			// “G‚Ì¶‘¶”»’è‚ğ—§‚Ä‚é
			isAliveEnemy_ = true;
		}
	}
	else // ƒQ[ƒ€ƒNƒŠƒA‚µ‚½‚ç“Gíœ
	{
		// “G‚Ì¶‘¶”»’è‚ğÜ‚é
		isAliveEnemy_ = false;
	}


}

void EnemyBase::Draw(void)
{
	// “G‚ÌÀ•W‚ğƒ‚ƒfƒ‹‚Éİ’è
	if (isAliveEnemy_)
	{
		// “Gƒ‚ƒfƒ‹•`‰æ
		MV1DrawModel(enemyModelId_);
	}
}



void EnemyBase::Release(void)
{
	// “Gƒ‚ƒfƒ‹‚ÌŠJ•ú
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


