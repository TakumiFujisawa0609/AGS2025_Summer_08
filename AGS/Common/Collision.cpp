#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/Application.h"
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
void Collision::Init(Player* player, StageBase* stage, EnemyManager* enemy, 
	Blood* blood, PlayerShot* pShot, Camera* camera, ItemManager* item)
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

	fKeyImg_ = LoadGraph("Data/Image/FKey.png");

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
	CollisionPAndItem();

	// プレイヤーとドアの当たり判定
	CollisionPAndD();
}

void Collision::Draw()
{
	if (isPickKey_)
	{
		// リロード中のキー画像を表示
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2 - 18, Application::SCREEN_SIZE_Y / 2 + 72, 0.14f, 0.0f, fKeyImg_, true);
		DrawFormatString(Application::SCREEN_SIZE_X / 2 - 3, Application::SCREEN_SIZE_Y / 2 + 64, 0xffffff, "拾う");
	}

	if (isOpenKey_)
	{
		// 開くキー画像を表示
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2 - 18, Application::SCREEN_SIZE_Y / 2 + 72, 0.14f, 0.0f, fKeyImg_, true);
		DrawFormatString(Application::SCREEN_SIZE_X / 2 - 3, Application::SCREEN_SIZE_Y / 2 + 64, 0xffffff, "開く");
	}

	DrawFormatString(500, 0,0xffffff, "isPickKey:%d", isPickKey_);
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
			dis = dis - 150;

			// 半径の合計
			float radiusNum = radiusP + radiusE;

			// 敵の攻撃アニメーションの再生時間を取得
			float animRate = enemy->GetAnimRate(); // 再生位置割合

			// 攻撃中だったら
			if (dis < radiusNum)
			{
				// 攻撃アニメの特定範囲内だけ当たり判定を有効にする（例）
				if (animRate >= 0.4f && animRate <= 0.6f)
				{
					if (!enemyAttackHit_[enemy])
					{
						player_->Damage(1);
						enemyAttackHit_[enemy] = true;
					}
				}
				else
				{
					// 攻撃範囲外ならフラグを戻す
					enemyAttackHit_[enemy] = false;
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
	const auto& enemies = enemy_->GetEnemies();
	auto& shots = pShot_->GetShots();  // 非constで書き換え可能に（SetAlive代わり）

	for (auto& shot : shots)
	{
		if (!shot.isAlive) continue;  // 死んでたらスキップ

		// プレイヤーショットの中心点（高さ調整）
		VECTOR centerPosPShot = VAdd(shot.pos, VGet(0, 0, 0));  // 調整不要ならそのまま

		for (auto pair : enemies)
		{
			for (EnemyBase* enemy : pair.second)
			{
				if (!enemy->GetAlive()) continue;

				// 敵の当たり判定用中心
				VECTOR centerPosE = VAdd(enemy->GetPos(), VGet(0, 100, 0));

				float dis = VSize(VSub(centerPosE, centerPosPShot));
				float rEnemy = 60.0f;
				float rPShot = 10.0f;
				float radiusNum = rEnemy + rPShot;

				if (dis < radiusNum)
				{
					enemy->Damage(1);
					shot.isAlive = false;  // 弾を消す

					blood_->Emit();
					blood_->SetAlive(true);
					blood_->SetPos(centerPosE);

					break;  // 1体に当たったら他の敵はスキップ（弾1発）
				}
			}
		}
	}
}

// プレイヤー弾とステージの当たり判定
void Collision::CollisionPShotAndS()
{
	int modelId = stage_->GetModelId();
	auto& shots = pShot_->GetShots();  // 複数弾に対応

	for (auto& shot : shots)
	{
		if (!shot.isAlive) continue;

		// 球体とステージの当たり判定
		hitPoly_PShot_S = MV1CollCheck_Sphere(modelId, -1, shot.pos, 10, -1);

		if (hitPoly_PShot_S.HitNum > 0)
		{
			shot.isAlive = false;
		}
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

// ワクチンとアイテムとの当たり判定
void Collision::CollisionPAndItem()
{
	const auto& items = item_->GetItems();

	isPickKey_ = false;

	// 連想配列（map）を for で回す
	for (auto pair : items)
	{
		for (ItemBase* item : pair.second)
		{
			// items = itemManager
			// item = itemBase

			// 衝突が有効状態なら、処理通過
			if (!item->IsCollisionState())
			{
				continue;
			}

			VECTOR pPos = player_->GetPPos();
			VECTOR vPos = item->GetPos();

			// プレイヤーの当たり判定の球体の中心点
			VECTOR pCenterPos = VAdd(pPos, VGet(0.0f, 110, 0));
			// ワクチンの当たり判定の球体の中心点
			VECTOR vCenterPos = VAdd(vPos, VGet(0, 50, 0));

			float radiusP = 45.0f;
			float radiusV = 230.0f;

			// 中心間の距離
			float dis = VSize(VSub(vCenterPos, pCenterPos));

			// 半径の合計
			float radiusNum = radiusP + radiusV;

			// 範囲内にいる状態で
			if (dis < radiusNum)
			{

				isPickKey_ = true;

				// Fを押したら
				if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_F))
				{
					// アイテム別処理
					switch (item->GetType())
					{
						// ワクチンの処理
					case ItemBase::TYPE::VACCINE:

						// ワクチンを拾う
						item_->PickVaccine();

						// アイテムの状態を変更
						item->ChangeState(ItemBase::STATE::PICKUP_V);
						break;

						// 弾薬箱の処理
					case ItemBase::TYPE::BULLET:

						// 弾薬箱を拾う
						item_->PickBulletBox();

						// アイテムの状態を変更
						item->ChangeState(ItemBase::STATE::PICKUP_B);
						break;
						// 救急キットの処理
					case ItemBase::TYPE::KIT:

						// 救急キットを拾う
						item_->PickKitBox();

						// アイテムの状態を変更
						item->ChangeState(ItemBase::STATE::PICKUP_K);
						break;

					}

				}
			}
		}
	}
}


// プレイヤーとドアの当たり判定
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


	// ワクチンがすべて拾われているか確認
	if (item_->GetVaccine() == 0)
	{

		// 範囲内にいる状態でFを押したら
		if (dis < radiusNum && InputManager::GetInstance().IsTrgDown(KEY_INPUT_F))

		// 範囲内にいる状態で
		if (dis < radiusNum)

		{
			isOpenKey_ = true;

			// Fを押したら
			if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_F))
			{
				// ドアが開いた音を再生
				SoundManager::GetInstance()->PlayOpen();

				// ワクチンがすべて拾われていたらゲームクリアへ遷移
				SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
			}
		}
		else
		{
			isOpenKey_ = false;
		}
	}
}

