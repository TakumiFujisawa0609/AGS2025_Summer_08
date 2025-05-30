#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Object/Player.h"
#include "../Object/StageBase.h"
#include "../Object/EnemyBase.h"
#include "../Object/Camera.h"
#include "../Object//PlayerShot.h"
#include "../Object/Blood.h"
#include "Collision.h"

// 初期化
void Collision::Init(Player* player, StageBase* stage, EnemyBase* enemy, Blast* blast, PlayerShot* pShot, Camera* camera)
{
	// ゲームシーンから渡されたインスタンスを使用
	player_ = player;
	stage_ = stage;
	enemy_ = enemy;
	blast_ = blast;
	pShot_ = pShot;
	camera_ = camera;

}

void Collision::Update()
{
	// プレイヤーと敵の当たり判定
	CollisionPAndE();

	// プレイヤー弾と敵の当たり判定
	CollisionPShotAndE();

	// プレイヤーとステージの当たり判定
	CollisionPAndS();

	// 敵とステージの当たり判定
	CollisionEAndS();
}

void Collision::Draw()
{
	//DrawSphere3D(pCenterPos_, 45, 10, 0x00ff00, 0x00ff00, false);	// プレイヤーの当たり判定の球体を描画
	//DrawFormatString(0, 400, 0xffffff, "pCenterPos_:(%.2f, %.2f, %.2f)", pCenterPos_.x, pCenterPos_.y, pCenterPos_.z);
	// プレイヤー座標
	player_->GetPPos();
	DrawFormatString(0, 420, 0xffffff, "コリジョン内のpPos:(%.2f, %.2f, %.2f)", player_->GetPPos().x, player_->GetPPos().y, player_->GetPPos().z);

	DrawFormatString(0, 320, 0xffffff, "Hit_E_S:%d", hitPoly_E_S.HitFlag);
	DrawFormatString(0, 340, 0xffffff, "Hit_E_P:%d", isHit_E_P_);

	DrawFormatString(600, 0, 0xffffff, "Hit_P_S:%d", isHit_P_S_);
	DrawFormatString(600, 20, 0xffffff, "Hit_Pshot_E:%d", hitPoly_PShot_E.HitFlag);

	DrawFormatString(0, 360, 0xffffff, "StartPos:(%.2f, %.2f, %.2f)", enemyPosS_.x, enemyPosS_.y, enemyPosS_.z);
	DrawFormatString(0, 380, 0xffffff, "EndPos(%.2f, %.2f, %.2f)", enemyPosE_.x, enemyPosE_.x, enemyPosE_.z);

	//DrawLine3D(enemyPosS_, enemyPosE_, 0xff0000);
	DrawLine3D(a, b, 0xff0000);
	//DrawSphere3D(enemyPosS_, 10, 10, 0xff0000, 0xff0000, false);	// 球を描画
}

void Collision::Release()
{
}

void Collision::CollisionPAndE()
{
	// 敵モデルのIDを取得
	int eModelId = enemy_->GetModelId();
	// プレイヤーの座標を取得
	VECTOR pPos = player_->GetPPos();
	// 敵の座標を取得
	VECTOR ePos = enemy_->GetPos();
	// プレイヤーの当たり判定の球体の中心点
	VECTOR pCenterPos = VAdd(pPos, VGet(0.0f, 110, 0));

	// プレイヤーと敵の当たり判定設定
	hitPoly_E_P = MV1CollCheck_Sphere(eModelId, -1, pCenterPos, 45.0f, -1);
	// 衝突した場合
	if (hitPoly_E_P.HitNum > 0)
	{
		// 停止フラグを立てる
		enemy_->SetStop(true); 

	}

#ifdef DEBUG
	// 衝突フラグを立てる
	isHit_ = hitPoly_E_P.HitNum != 0;	
	// プレイヤー中心座標
	pCenterPos_ = pCenterPos;
#endif // DEBUG

}

void Collision::CollisionPShotAndE(void)
{
	int eModelId = enemy_->GetModelId();

	// 
	VECTOR shotPos = pShot_->GetPos();
	VECTOR dir = pShot_->GetDir();
	float maxShotPos = 1000.0f;

	// endPos は shotPos から dir 方向に maxDistance 進んだ地点
	VECTOR endPos = VAdd(shotPos, VScale(dir, maxShotPos));

	// 球体と敵モデルとの当たり判定
	hitPoly_PShot_E = MV1CollCheck_Line(eModelId, -1, shotPos, endPos, -1); 

	if (hitPoly_PShot_E.HitFlag == 1)
	{
		enemy_->SetAlive(false);
	}

#ifdef DEBUG
	a = shotPos;
	b = endPos;
#endif // DEBUG
}

void Collision::CollisionPAndS()
{
	// ステージのモデルIDを取得
	int modelId = stage_->GetModelId();
	// プレイヤーの座標を取得
	VECTOR pos = player_->GetPPos();
	// プレイヤーの当たり判定の球体の中心点
	// 敵プレイヤーの移動予定地を取得
	VECTOR movedPos = player_->GetMovedPos();

	// 移動ベクトル（向き）
	VECTOR dir = VSub(movedPos, pos);   // 移動方向ベクトル
	dir = VNorm(dir);             // 正規化（長さを1にする）
	dir = VScale(dir, 150.0f);    // 任意の長さにスケーリング
	VECTOR endPos = VAdd(pos, dir); // pos から伸ばした終点

	// XとY座標をレイの補正値に固定
	pos.y =endPos.y = RAY_COL_Y;

	// 敵とステージの当たり判定設定
	hitPoly_P_S = MV1CollCheck_Line(modelId, -1, pos, endPos, -1);

	//敵とステージが衝突した場合
	if (hitPoly_P_S.HitFlag == 1)
	{
		player_->SetStop(true);	// 停止
	}
	else
	{
		player_->SetStop(false);	// 停止フラグ解除
	}


#ifdef _DEBUG

	isHit_P_S_ = hitPoly_P_S.HitFlag;
#endif // _DEBUG
}

void Collision::CollisionEAndS()
{
	// ステージのモデルIDを取得
	int eModelId = stage_->GetModelId();
	// 敵の座標を取得
	VECTOR pos = enemy_->GetPos();
	// 敵の移動予定地を取得
	VECTOR movedPos = enemy_->GetMovedPos();

	// Y座標をレイの補正値に固定
	pos.y = movedPos.y = RAY_COL_Y;

	// 敵とステージの当たり判定設定
	hitPoly_E_S = MV1CollCheck_Line(eModelId, -1, pos, movedPos);
	
	//敵とステージが衝突した場合
	if (hitPoly_E_S.HitFlag == 1)
	{
		enemy_->SetStop(true);	// 停止
	}
	else
	{
		enemy_->SetStop(false);	// 停止フラグ解除
	}

#ifdef _DEBUG


	enemyPosS_ = pos;
	enemyPosE_ = movedPos;
#endif // _DEBUG

}

