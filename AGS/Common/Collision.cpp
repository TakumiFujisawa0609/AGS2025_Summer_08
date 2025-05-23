#include <DxLib.h>
#include "../Object/Player.h"
#include "../Object/StageBase.h"
#include "../Object/EnemyBase.h"
#include "../Object/Blood.h"
#include "Collision.h"

// 初期化
void Collision::Init(Player* player, StageBase* stage, EnemyBase* enemy, Blast* blast, PlayerShot* pShot)
{
	// ゲームシーンから渡されたインスタンスを使用
	player_ = player;
	stage_ = stage;
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

	// 敵とステージの当たり判定
	CollisionEAndStage();
}

void Collision::Draw()
{
	DrawFormatString(0, 120, 0xffffff, "Hit:%d", hitPoly.HitFlag);
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

void Collision::CollisionEAndStage()
{
	// ステージのモデルIDを取得
	int modelId = stage_->GetModelId();

	// 敵の座標を取得
	VECTOR pos = enemy_->GetPos();
	// 敵の移動予定地を取得
	VECTOR movedPos = enemy_->GetMovedPos();
	float r = 33;

	VECTOR startPos = { pos.x, RAY_COL_Y, pos.z };		// レイの開始地点座標のY座標を200に固定
	VECTOR endPos = { movedPos.x, RAY_COL_Y, movedPos.z }; // レイを飛ばす先をY座標を200に固定

	// 敵とステージの当たり判定設定
	hitPoly = (MV1CollCheck_Line(modelId, -1, startPos, endPos));
	
	//敵とステージが衝突した場合
	if (hitPoly.HitFlag == 1)
	{
		enemy_->SetStop(true);	// 停止
	}
	else
	{
		enemy_->SetStop(false);	// 停止フラグ解除
	}
}

