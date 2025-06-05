#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Common/AnimControl.h"
#include "../Object/Player.h"
#include "../Object/StageBase.h"
#include "../Manager/EnemyManager.h"
#include "../Manager/ItemManager.h"
#include "../Object/Camera.h"
#include "../Object//PlayerShot.h"
#include "../Object/Blood.h"
#include "Collision.h"

// 初期化
void Collision::Init(Player* player, StageBase* stage, EnemyManager* enemy, Blood* blood, PlayerShot* pShot, Camera* camera, ItemManager* item)
{
	// ゲームシーンから渡されたインスタンスを使用
	player_ = player;
	stage_ = stage;
	enemy_ = enemy;
	blood_ = blood;
	pShot_ = pShot;
	camera_ = camera;
	item_ = item;

	// 敵を取得
	const auto& enemies = enemy_->GetEnemies();

	// 連想配列（map）を for で回す
	for (auto pair : enemies)
	{
		for (EnemyBase* enemy : pair.second)
		{
			enemyAttackHit_[enemy] = false;
		}
	}

	const auto& items = item_->GetItems();

	// 連想配列（map）を for で回す
	for (auto pair : items)
	{
		for (ItemBase* item : pair.second)
		{
			itemHit_[item] = false;
		}
	}

}

void Collision::Update()
{
	// プレイヤーと敵の当たり判定
	CollisionPAndE();

	// プレイヤー弾と敵の当たり判定
	CollisionPShotAndE();
	// プレイヤー弾とステージの当たり判定
	CollisionPShotAndS();

	// プレイヤーとステージの当たり判定
	CollisionPAndS();

	// 敵とステージの当たり判定
	CollisionEAndS();

	// プレイヤーとワクチンの当たり判定
	CollisionPAndV();

	// プレイヤーとドアの当たり判定
	CollisionPAndD();
}

void Collision::Draw()
{
	////DrawSphere3D(pCenterPos_, 45, 10, 0x00ff00, 0x00ff00, false);	// プレイヤーの当たり判定の球体を描画
	////DrawFormatString(0, 400, 0xffffff, "pCenterPos_:(%.2f, %.2f, %.2f)", pCenterPos_.x, pCenterPos_.y, pCenterPos_.z);
	//// プレイヤー座標
	//player_->GetPPos();
	//DrawFormatString(0, 420, 0xffffff, "コリジョン内のpPos:(%.2f, %.2f, %.2f)", player_->GetPPos().x, player_->GetPPos().y, player_->GetPPos().z);

	//DrawFormatString(0, 320, 0xffffff, "Hit_E_S:%d", hitPoly_E_S.HitFlag);
	//DrawFormatString(0, 640, 0xffffff, "Hit_E_P:%d", isHit_E_P_);

	//DrawFormatString(600, 0, 0xffffff, "Hit_P_S:%d", isHit_P_S_);
	////DrawFormatString(600, 20, 0xffffff, "Hit_PShot_E:%d", hitPoly_PShot_E.HitFlag);

	//DrawFormatString(0, 360, 0xffffff, "StartPos:(%.2f, %.2f, %.2f)", enemyPosS_.x, enemyPosS_.y, enemyPosS_.z);
	//DrawFormatString(0, 380, 0xffffff, "EndPos(%.2f, %.2f, %.2f)", enemyPosE_.x, enemyPosE_.x, enemyPosE_.z);

	////DrawLine3D(enemyPosS_, enemyPosE_, 0xff0000);
	//DrawLine3D(a, b, 0xff0000);
	////DrawSphere3D(enemyPosS_, 10, 10, 0xff0000, 0xff0000, false);	// 球を描画

	//DrawFormatString(600, 20, 0xffffff, "HitP_V:%d", isHitP_V_);

	//int y = 500;
	//for (const auto& pair : enemyAttackHit_)
	//{
	//	DrawFormatString(700, y, 0xffffff, "Enemy[%p] Hit:%d", pair.first, pair.second);
	//	y += 30;
	//}
	//// アイテム
	//int y2 = 650;
	//for (const auto& pair : itemHit_)
	//{
	//	DrawFormatString(700, y2, 0xffffff, "item[%p] Hit:%d", pair.first, pair.second);
	//	y += 30;
	//}

	//int animRateY = 100;
	//for (const auto& pair : enemy_->GetEnemies())
	//{
	//	for (EnemyBase* enemy : pair.second)
	//	{
	//		if (enemy->GetState() == EnemyBase::STATE::ATTACK)
	//		{
	//			{
	//				float animRate = enemy->GetAnimRate(); // 0.0〜1.0 の範囲
	//				DrawFormatString(900, animRateY, 0xffaa00, "Enemy[%p] AnimRate: %.2f", enemy, animRate);
	//				animRateY += 30;
	//			}
	//		}
	//	}
	//}


}

void Collision::Release()
{
}

void Collision::CollisionPAndE()
{
	const auto& enemies = enemy_->GetEnemies();

	// 連想配列（map）を for で回す
	for (auto pair : enemies)
	{
		for (EnemyBase* enemy : pair.second)
		{
			// 敵が攻撃状態以外ならスキップ（重要）
			if (enemy->GetState() != EnemyBase::STATE::ATTACK) continue;
			
			// プレイヤーの座標を取得
			VECTOR pPos = player_->GetPPos();
			// 敵の座標を取得
			VECTOR ePos = enemy->GetPos();
			
			// プレイヤーの当たり判定の球体の中心点
			VECTOR pCenterPos = VAdd(pPos, VGet(0.0f, 110, 0));
			// 敵の当たり判定の球体の中心点
			VECTOR eCenterPos = VAdd(ePos, VGet(0, 100, 0));

			float radiusP = 45.0f;
			float radiusE = 60.0f;

			// 中心間の距離
			float dis = VSize(VSub(pCenterPos,eCenterPos));
			dis = dis - 100;

			// 半径の合計
			float radiusNum = radiusP + radiusE;

			// 敵の攻撃アニメーションの再生時間を取得
			float animRate = enemy->GetAnimRate(); // 再生位置割合

			// 攻撃中だったら
			if (dis < radiusNum)
			{
				if (!enemyAttackHit_[enemy]) // 前のフレームで当たってなかったら
				{
					// 指定したアニメ範囲内でしか攻撃ヒットを認めない
					//if (animRate >= 0.5f && animRate <= 0.6f)
					//{
						player_->Damage(1);
					//}
					enemyAttackHit_[enemy] = true;
				}
			}
			else
			{
				enemyAttackHit_[enemy] = false;
			}
		}
	}

}

void Collision::CollisionPShotAndE(void)
{
	//int eModelId = enemy_->GetModelId();

	//// 
	//VECTOR shotPos = pShot_->GetPos();
	//VECTOR dir = pShot_->GetDir();
	//float maxShotPos = 1000.0f;

	//// endPos は shotPos から dir 方向に maxDistance 進んだ地点
	//VECTOR endPos = VAdd(shotPos, VScale(dir, maxShotPos));

	//// 球体と敵モデルとの当たり判定
	//hitPoly_PShot_E = MV1CollCheck_Line(eModelId, -1, shotPos, endPos, -1);

	//if (hitPoly_PShot_E.HitFlag == 1)
	//{
	//	enemy_->SetAlive(false);

	//	a = shotPos;
	//	b = endPos;
	//}

	if (!pShot_->GetAlive()) return; // 弾が無いなら判定しない

	const auto& enemies = enemy_->GetEnemies();

	// 連想配列（map）を for で回す
	for (auto pair : enemies)
	{
		for (EnemyBase* enemy : pair.second)
		{
			if (!enemy->GetAlive()) continue;  // 死んだ敵はスキップ
			// 中心点
			VECTOR centerPosE = enemy->GetPos();
			centerPosE = VAdd(centerPosE, VGet(0, 100, 0));
			// 中心点
			VECTOR centerPosPShot = pShot_->GetPos();

			// 中心点間の距離
			float dis = VSize(VSub(centerPosE, centerPosPShot));
			// 半径
			float rEnemy = 60.0f;
			float rPShot = 10.0f;
			float radiusNum = rEnemy + rPShot;

			// 当たったら
			if (dis < radiusNum)
			{
				enemy->SetAlive(false);
				pShot_->SetAlive(false);  // 弾を消す

				blood_->Emit();
				blood_->SetAlive(true);
				blood_->SetPos(centerPosE);
			}
		}
	}

#ifdef DEBUG
		a = shotPos;
		b = endPos;
#endif // DEBUG
}

// プレイヤー弾とステージの当たり判定
void Collision::CollisionPShotAndS()
{
	int modelId = stage_->GetModelId();
	VECTOR pos = pShot_->GetPos();

	hitPoly_PShot_S = MV1CollCheck_Sphere(modelId, -1, pos, 10, -1);

	if (hitPoly_PShot_S.HitNum > 0)
	{
		pShot_->SetAlive(false);
	}
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
	pos.y = endPos.y = RAY_COL_Y;

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
	const auto& enemies = enemy_->GetEnemies();

	// 連想配列（map）を for で回す
	for (auto pair : enemies)
	{
		// pair.first : EnemyBase::TYPE（型）
		// pair.second : std::vector<EnemyBase*>（敵リスト）
		for (EnemyBase* enemy : pair.second)
		{
			// ステージのモデルIDを取得
			int eModelId = stage_->GetModelId();
			// 敵の座標を取得
			VECTOR pos = enemy->GetPos();
			// 敵の移動予定地を取得
			VECTOR movedPos = enemy->GetMovedPos();

			// Y座標をレイの補正値に固定
			pos.y = movedPos.y = RAY_COL_Y;

			// 敵とステージの当たり判定設定
			hitPoly_E_S = MV1CollCheck_Line(eModelId, -1, pos, movedPos);

			//敵とステージが衝突した場合
			if (hitPoly_E_S.HitFlag == 1)
			{
				enemy->SetStop(true);	// 停止
			}
			else
			{
				enemy->SetStop(false);	// 停止フラグ解除
			}



#ifdef _DEBUG


			enemyPosS_ = pos;
			enemyPosE_ = movedPos;
#endif // _DEBUG
		}
	}

}

void Collision::CollisionPAndV()
{
	const auto& items = item_->GetItems();

	// 連想配列（map）を for で回す
	for (auto pair : items)
	{
		for (ItemBase* item : pair.second)
		{
			VECTOR pPos = player_->GetPPos();
			VECTOR vPos = item->GetPos();

			// プレイヤーの当たり判定の球体の中心点
			VECTOR pCenterPos = VAdd(pPos, VGet(0.0f, 110, 0));
			// 敵の当たり判定の球体の中心点
			VECTOR vCenterPos = VAdd(vPos, VGet(0, 50, 0));

			float radiusP = 45.0f;
			float radiusV = 230.0f;

			// 中心間の距離
			float dis = VSize(VSub(vCenterPos, pCenterPos));

			// 半径の合計
			float radiusNum = radiusP + radiusV;

			if (dis < radiusNum && InputManager::GetInstance()->IsTrgDown(KEY_INPUT_F))
			{
				item->SetPickUp();

				itemHit_[item] = true;
			}
			else
			{
				itemHit_[item] = false;
			}
		}
	}
}

void Collision::CollisionPAndD()
{
	VECTOR pPos = player_->GetPPos();
	VECTOR dPos = stage_->GetDPos();

	// プレイヤーの当たり判定の球体の中心点
	VECTOR pCenterPos = VAdd(pPos, VGet(0.0f, 110, 0));
	// ドアの当たり判定の球体の中心点
	VECTOR dCenterPos = VAdd(dPos, VGet(0,200, 0));

	float radiusP = 45.0f;
	float radiusD = 165.0f;

	// 中心間の距離
	float dis = VSize(VSub(dCenterPos, pCenterPos));

	// 半径の合計
	float radiusNum = radiusP + radiusD;

	const auto& items = item_->GetItems();

	// 連想配列（map）を for で回す
	for (auto pair : items)
	{
		for (ItemBase* item : pair.second)
		{
			if (dis < radiusNum
				&& InputManager::GetInstance()->IsTrgDown(KEY_INPUT_F)
				&& item->GetPickUp())
			{
				SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);

				SoundManager::GetInstance()->PlayOpen();
			}
		}
	}
}

