#include "Collision.h"
#include <DxLib.h>
#include "Player.h"
#include "EnemyBase.h"
#include "Blood.h"
#include "PlayerShot.h"

// 初期化
void Collision::Init(Player* player, EnemyBase* enemy, Blast* blast, PlayerShot* pShot)
{
	// ゲームシーンから渡されたインスタンスを使用
	player_ = player;
	enemy_ = enemy;
	blast_ = blast;
	pShot_ = pShot;

}

// 更新
void Collision::Update(void)
{
	// プレイヤーと敵の当たり判定
	CollisionPAndE();

	// プレイヤー弾と敵の当たり判定
	CollisionPShotAndE();
}

// 描画
void Collision::Draw(void)
{

}

// 解放
void Collision::Release(void)
{

}

void Collision::CollisionPAndE(void)
{
}

void Collision::CollisionPShotAndE(void)
{
}
