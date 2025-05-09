#include <DxLib.h>
#include "../Object/Player.h"
#include "../Object/EnemyBase.h"
#include "../Object/Blood.h"
#include "Collision.h"

// 初期化
void Collision::Init(Player* player, EnemyBase* enemy, Blast* blast, PlayerShot* pShot)
{
	// ゲームシーンから渡されたインスタンスを使用
	player_ = player;
	enemy_ = enemy;
	blast_ = blast;
	pShot_ = pShot;

}

void Collision::Update()
{
	// プレイヤーと敵の当たり判定
	CollisionPAndE();

	// プレイヤー弾と敵の当たり判定
	CollisionPShotAndE();
}

void Collision::Draw()
{
}

void Collision::Release()
{
}

void Collision::CollisionPAndE(void)
{
}

void Collision::CollisionPShotAndE(void)
{
}
