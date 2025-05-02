#include "Collision.h"
#include <DxLib.h>
#include "Player.h"
#include "Enemy.h"
#include "Blast.h"
#include "PlayerShot.h"

// 初期化
void Collision::Init(Player* player, Enemy* enemy, Blast* blast, PlayerShot* pShot)
{
	// ゲームシーンから渡されたインスタンスを使用
	player_ = player;
	enemy_ = enemy;
	blast_ = blast;
	pShot_ = pShot;

	// プレイヤーと敵の当たり判定用球体の半径の合計
	radiusPAndESum_ = INIT_PLAYER_SPHERE_RADIUS + INIT_ENEMY_SPHERE_RADIUS;
	// プレイヤー弾と敵の当たり判定用球体の半径の合計
	radiusPShotAndESum_ = INIT_P_SHOT_SPHERE_RADIUS + INIT_ENEMY_SPHERE_RADIUS;

	// プレイヤーと敵の当たり判定用球体の中心間の距離の初期化
	centerDistancePandE_ = VSize(VSub(player_->INIT_PLAYER_POS, enemy_->INIT_ENEMY_POS));
	// プレイヤー弾と敵の当たり判定用球体の半径の初期化
	centerDistancePShotAndE_ = VSize(VSub(pShot_->INIT_P_SHOT_POS, enemy_->INIT_ENEMY_POS));

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

	//// プレイヤーの衝突判定確認用球体描画
	//DrawSphere3D(player_->GetPlayerPos(), playerSphereRadius_, 10.0f, 0x0000ff, 0x0000ff, false);
	//// 敵の衝突判定確認用球体描画
	//DrawSphere3D(enemy_->GetEnemyPos(), enemySphereRadius_, 10.0f, 0x0000ff, 0x0000ff, false);
	//// フラグ関係デバッグ用
	//DrawFormatString(0, 0, 0xffffff, "isAliveP: %d, isAliveE: %d, isBlast: %d, canMove: %d", player_->GetIsAlivePlayer(), enemy_->GetIsAliveEnemy(), blast_->GetIsBlast(), player_->GetIsPlayerCanMove());
	//// 当たり判定用に使う計算の結果をデバック用に表示
	//DrawFormatString(0, 20, 0xffffff, "centerDistancePandE: %f", centerDistancePandE_);
	//DrawFormatString(0, 40, 0xffffff, "centerDistancePShotAndE: %f", centerDistancePShotAndE_);

}

// 解放
void Collision::Release(void)
{

}

void Collision::CollisionPAndE(void)
{
	// 当たり判定用球体の中心間の距離
	centerDistancePandE_ = VSize(VSub(player_->GetPlayerPos(), enemy_->GetEnemyPos()));

	// プレイヤーと敵の当たり判定
	// プレイヤーと敵が生きている時
	if (player_->GetIsAlivePlayer() && enemy_->GetIsAliveEnemy())
	{
		// プレイヤーと敵が衝突したら
		if (centerDistancePandE_ < radiusPAndESum_)
		{
			// プレイヤーを死んだ状態にする
			player_->SetIsAlivePlayer(false);
			// プレイヤーを移動不可にする
			player_->SetIsPlayerCanMove(false);
			// 爆発アニメーション開始
			blast_->SetIsBlast(true);
			// 爆発座標をプレイヤーの座標にする
			blast_->SetBlastPos(player_->GetPlayerPos());
		}
	}


}

void Collision::CollisionPShotAndE(void)
{
	// プレイヤー弾と敵の当たり判定
	// プレイヤー弾と敵が生きている時
	if (pShot_->GetAnyPShotAlive() && enemy_->GetIsAliveEnemy())
	{
		// プレイヤー弾と敵の当たり判定用球体の中心間の距離
		centerDistancePShotAndE_ = VSize(VSub(pShot_->GetPShotPos(), enemy_->GetEnemyPos()));
		centerDistanceAbnormalPShotAndE1_ = VSize(VSub(pShot_->GetAbnormalPShotPos1(), enemy_->GetEnemyPos()));
		centerDistanceAbnoemalPShotAndE2_ = VSize(VSub(pShot_->GetAbnormalPShotPos2(), enemy_->GetEnemyPos()));

		// プレイヤー弾と敵が衝突したら
		if (centerDistancePShotAndE_ < radiusPShotAndESum_ || centerDistanceAbnormalPShotAndE1_ < radiusPAndESum_
			|| centerDistanceAbnoemalPShotAndE2_ < radiusPAndESum_)
		{
			// 敵を死んだ状態にする
			enemy_->SetIsAliveEnemy(false);
			// 爆発アニメーション開始
			blast_->SetIsBlast(true);
			// 爆発座標を敵の座標にする
			blast_->SetBlastPos(enemy_->GetEnemyPos());
			// プレイヤー弾を死んだ状態にする
			pShot_->SetAnyAlivePShot(false);
			pShot_->SetIsAlivePShot(false);
			pShot_->SetIsAliveAbnormalPShot1(false);
			pShot_->SetIsAliveAbnormalPShot2(false);

		}
	}
}
