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

void Collision::CollisionEAndStage(void)
{
	// ステージのモデルIDを取得
	int modelId = stage_->GetModelId();
	// 敵の座標を取得
	VECTOR pos = enemy_->GetPos();
	// 敵の移動予定地を取得
	VECTOR nextPos = enemy_->GetNextPos();
	// 敵の当たり判定の球体の半径
	//COLLISION_HIT_RESULT result;
	// 敵とステージが当たっていたら
	//(MV1CollCheck_Line(modelId, -1, pos, nextPos, -1));
	//{
	//	// 敵をストップさせる
	//	enemy_->SetIsStop(true);
	//}
}
