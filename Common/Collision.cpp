#include <algorithm>
#include <DxLib.h>
#include "../Utility/AsoUtility.h"
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
	qKeyImg_ = LoadGraph("Data/Image/QKey.png");

	vImage_ = LoadGraph("Data/Image/GetVaccine.png");
	sImage_ = LoadGraph("Data/Image/GetShot.png");
	kImage_ = LoadGraph("Data/Image/GeyKit.png");

	order02Img_ = LoadGraph("Data/Image/order/order02.png");
	order03Img_ = LoadGraph("Data/Image/order/order03.png");

	isGameClear_ = false;
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
	//CollisionEAndS();

	// プレイヤーとワクチンの当たり判定
	CollisionPAndItem();

	// プレイヤーとドアの当たり判定
	CollisionPAndD();

	// トリガーが発生したらカウント開始
	if (isTrgger_)
	{
		if (!isTriggerStarted_)
		{
			isTriggerStarted_ = true;
			triggerTimer_ = 0.0f;  // 初期化
		}
		else
		{
			triggerTimer_ += SceneManager::GetInstance()->GetDeltaTime();
		}
	}
}

void Collision::Draw()
{
	if (isPickKey_)
	{
		// リロード中のキー画像を表示
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2 - 18, Application::SCREEN_SIZE_Y / 2 + 72, 0.23f, 0.0f, fKeyImg_, true);
		SetFontSize(23);
		DrawFormatString(Application::SCREEN_SIZE_X / 2 + 5, Application::SCREEN_SIZE_Y / 2 + 61, 0xffffff, "拾う");
	}

	if (isOpenKey_)
	{
		// 開くキー画像を表示
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2 - 18, Application::SCREEN_SIZE_Y / 2 + 95, 0.23f, 0.0f, fKeyImg_, true);
		SetFontSize(23);
		DrawFormatString(Application::SCREEN_SIZE_X / 2 + 4, Application::SCREEN_SIZE_Y / 2 + 83, 0xffffff, "開く");
	}

	if (isClosekey_)
	{
		SetFontSize(23);
		DrawFormatString(Application::SCREEN_SIZE_X / 2 - 100, Application::SCREEN_SIZE_Y / 2 + 350, 0xffffff, "左クリックで閉じる");
	}

	if (player_->GetHp() == 1 && player_->GetHeal() >= 1)
	{
		// 開くキー画像を表示
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2 - 38, Application::SCREEN_SIZE_Y / 2 + 98, 0.23f, 0.0f, qKeyImg_, true);
		SetFontSize(23);
		DrawFormatString(Application::SCREEN_SIZE_X / 2 - 17, Application::SCREEN_SIZE_Y / 2 + 86, 0xffffff, "長押しで回復");
	}

	SetFontSize(20);
	// 回復可能数
	DrawFormatString(1606, 967, 0xffffff, "%d", player_->GetHeal());

	if (player_->GetHp() == 1)
	{
		DrawGraph(0, 0, defoHandle_, true);

		// alpha値計算
		int alpha = (int)(((sin(count * 0.05) * 0.5) + 0.5) * 255 + 30); // 0〜255
		SoundManager::GetInstance()->PlayDamage();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(0, 0, damegeHandle_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		count = count + 1; // 毎フレーム増やす
	}
	else
	{
		SoundManager::GetInstance()->StopDamage();
	}

	if (item_->IsShowingGetVaccine())
	{
		// 表示する画像
		DrawRotaGraph(960, 540, 0.6, 0, vImage_, true);
		isClosekey_ = true;

		// マウス左クリックで非表示にして再開
		if (InputManager::GetInstance().IsTrgMouseLeft())
		{
			item_->SetIsShowingGetVaccine(false);
			isClosekey_ = false;
		}
	}
	if (item_->IsShowingGetShot())
	{
		// 表示する画像
		DrawRotaGraph(960, 540, 0.6, 0, sImage_, true);
		isClosekey_ = true;

		// マウス左クリックで非表示にして再開
		if (InputManager::GetInstance().IsTrgMouseLeft())
		{
			item_->SetIsShowingGetShot(false);
			isClosekey_ = false;

			if (item_->IsTrigger())
			{
				SoundManager::GetInstance()->StopOrder1();
				SoundManager::GetInstance()->PlayOrder2();
				isTrgger_ = true;
			}
		}
	}
	if (item_->IsShowingGetKit())
	{
		// 表示する画像
		DrawRotaGraph(960, 540, 0.6, 0, kImage_, true);
		isClosekey_ = true;

		// マウス左クリックで非表示にして再開
		if (InputManager::GetInstance().IsTrgMouseLeft())
		{
			item_->SetIsShowingGetKit(false);
			isClosekey_ = false;

			if (item_->IsTrigger())
			{
				SoundManager::GetInstance()->StopOrder1();
				SoundManager::GetInstance()->PlayOrder2();
				isTrgger_ = true;
			}
		}
	}

	const auto& enemies = enemy_->GetEnemies();
	for (auto pair : enemies)
	{
		for (EnemyBase* enemy : pair.second)
		{
			if (!enemy->GetAlive()) continue;

			// 敵の当たり判定用中心
			VECTOR centerPosE = VAdd(enemy->GetPos(), VGet(0, 95, 0));

			float rEnemy = 65.0f;

			//DrawSphere3D(centerPosE, rEnemy, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
		}
	}

	// トリガーから10秒以内は画像1、10秒経過後は画像2
	if (isTriggerStarted_)
	{
		if (SoundManager::GetInstance()->IsPlayOrder2())
		{
			if (triggerTimer_ < 10.0f)
			{
				DrawGraph(0, 0, order02Img_, true); // 1枚目
			}
			else
			{
				DrawGraph(0, 0, order03Img_, true); // 2枚目
			}
		}
	}

#ifdef _DEBUG

	//for (auto pair : enemies)
	//{
	//	for (EnemyBase* enemy : pair.second)
	//	{
	//		if (!enemy->GetAlive()) continue;

	//		int modelId = enemy->GetModelId();

	//		// 頭の座標と半径（頭の当たり判定は球体）
	//		int head = MV1SearchFrame(modelId, "mixamorig:Head");
	//		VECTOR headPos = MV1GetFramePosition(modelId, head);
	//		float headRadius = 15.0f;

	//		// 頭の球を赤色で描画
	//		DrawSphere3D(headPos, headRadius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), false);

	//		// 胴体のOBBを黄色で描画
	//		int body = MV1SearchFrame(modelId, "mixamorig:Neck");
	//		int hip = MV1SearchFrame(modelId, "mixamorig:Hips");

	//		VECTOR top = MV1GetFramePosition(modelId, body);
	//		VECTOR bottom = MV1GetFramePosition(modelId, hip);

	//		DrawDebugOBB(top, bottom, 15.5f);

	//		// 左腕など他の部位のOBBも同様に描画
	//		// 左上腕
	//		int LeftArm = MV1SearchFrame(modelId, "mixamorig:LeftArm");
	//		int LeftForeArm = MV1SearchFrame(modelId, "mixamorig:LeftForeArm");
	//		VECTOR leftArmPos = MV1GetFramePosition(modelId, LeftArm);
	//		VECTOR leftForeArmPos = MV1GetFramePosition(modelId, LeftForeArm);
	//		DrawDebugOBB(leftArmPos, leftForeArmPos, 9.0f);

	//		// 左前腕
	//		int LeftHand = MV1SearchFrame(modelId, "mixamorig:LeftHandMiddle1");
	//		VECTOR leftHandPos = MV1GetFramePosition(modelId, LeftHand);
	//		DrawDebugOBB(leftForeArmPos, leftHandPos, 6.0f);

	//		// 右上腕
	//		int RightArm = MV1SearchFrame(modelId, "mixamorig:RightArm");
	//		int RightForeArm = MV1SearchFrame(modelId, "mixamorig:RightForeArm");
	//		VECTOR rightArmPos = MV1GetFramePosition(modelId, RightArm);
	//		VECTOR rightForeArmPos = MV1GetFramePosition(modelId, RightForeArm);
	//		DrawDebugOBB(rightArmPos, rightForeArmPos, 9.0f);

	//		// 右前腕
	//		int RightHand = MV1SearchFrame(modelId, "mixamorig:RightHand");
	//		VECTOR rightHandPos = MV1GetFramePosition(modelId, RightHand);
	//		DrawDebugOBB(rightForeArmPos, rightHandPos, 6.0f);

	//		// 左太もも
	//		int LeftUpLeg = MV1SearchFrame(modelId, "mixamorig:LeftUpLeg");
	//		int LeftLeg = MV1SearchFrame(modelId, "mixamorig:LeftLeg");
	//		VECTOR leftUpLegPos = MV1GetFramePosition(modelId, LeftUpLeg);
	//		VECTOR leftLegPos = MV1GetFramePosition(modelId, LeftLeg);
	//		DrawDebugOBB(leftUpLegPos, leftLegPos, 10.0f);

	//		// 左脛
	//		int LeftFoot = MV1SearchFrame(modelId, "mixamorig:LeftFoot");
	//		VECTOR leftFootPos = MV1GetFramePosition(modelId, LeftFoot);
	//		DrawDebugOBB(leftLegPos, leftFootPos, 6.0f);

	//		// 右太もも
	//		int RightUpLeg = MV1SearchFrame(modelId, "mixamorig:RightUpLeg");
	//		int RightLeg = MV1SearchFrame(modelId, "mixamorig:RightLeg");
	//		VECTOR rightUpLegPos = MV1GetFramePosition(modelId, RightUpLeg);
	//		VECTOR rightLegPos = MV1GetFramePosition(modelId, RightLeg);
	//		DrawDebugOBB(rightUpLegPos, rightLegPos, 10.0f);

	//		// 右脛
	//		int RightFoot = MV1SearchFrame(modelId, "mixamorig:RightFoot");
	//		VECTOR rightFootPos = MV1GetFramePosition(modelId, RightFoot);
	//		DrawDebugOBB(rightLegPos, rightFootPos, 6.0f);
	//	}
	//}
#endif
}

void Collision::Release()
{
	DeleteGraph(qKeyImg_);

	DeleteGraph(vImage_);
	DeleteGraph(sImage_);
	DeleteGraph(kImage_);

	DeleteGraph(damegeHandle_);
	DeleteGraph(defoHandle_);

	DeleteGraph(order02Img_);
	DeleteGraph(order03Img_);
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
			VECTOR eCenterPos = VAdd(ePos, VGet(0, 95, 0));

			float radiusP = 45.0f;
			float radiusE = 70.0f;

			// 中心間の距離
			float dis = VSize(VSub(pCenterPos,eCenterPos));
			dis = dis - 150;

			// 半径の合計
			float radiusNum = radiusP + radiusE;

			// 敵の攻撃アニメーションの再生時間を取得
			float animRate = enemy->GetAnimRate(); // 再生位置割合

			// 攻撃中だったら
			if (dis < radiusNum && player_->GetAlive())
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

		for (auto pair : enemies)
		{
			for (EnemyBase* enemy : pair.second)
			{
				if (!enemy->GetAlive()) continue;

				int eModelId = enemy->GetModelId();

				float headRad = 15;	// 頭の半径
				float pShotRad = 0.1f;	// 弾の半径
				// フレーム
				int head = MV1SearchFrame(eModelId, "mixamorig:Head");
				// 頭の座標
				VECTOR headPos = MV1GetFramePosition(eModelId, head);

				// 線分距離
				float dist1 = DistanceFromLineSegment(shot.prevPos, shot.pos, headPos);

				// 頭
				if (dist1 < (pShotRad + headRad))
				{
					enemy->Damage(3);
					shot.isAlive = false;

					blood_->SetAlive(true);
					blood_->SetPos(shot.pos);
					blood_->Emit();

					SceneManager::GetInstance()->SetHeadShot(1);

					break;  // 1体に当たったら他の敵はスキップ（弾1発）
				}

				// 胴体
				int body = MV1SearchFrame(eModelId, "mixamorig:Neck");
				int hip = MV1SearchFrame(eModelId, "mixamorig:Hips");
				VECTOR bodyPos = MV1GetFramePosition(eModelId, body);
				VECTOR hipPos = MV1GetFramePosition(eModelId, hip);

				if (IsHitLineSegmentAndOBB(shot.prevPos, shot.pos, bodyPos, hipPos, 15.5f))
				{
					shot.isAlive = false;
					enemy->Damage(1);

					blood_->SetAlive(true);
					blood_->SetPos(shot.pos);
					blood_->Emit();
					break;
				}

				// 左上腕
				int LeftArm = MV1SearchFrame(eModelId, "mixamorig:LeftArm");
				int LeftForeArm = MV1SearchFrame(eModelId, "mixamorig:LeftForeArm");
				VECTOR leftArmPos = MV1GetFramePosition(eModelId, LeftArm);
				VECTOR leftForeArmPod = MV1GetFramePosition(eModelId, LeftForeArm);

				if (IsHitLineSegmentAndOBB(shot.prevPos, shot.pos, leftArmPos, leftForeArmPod, 9.0f))
				{
					shot.isAlive = false;
					enemy->Damage(1);

					blood_->SetAlive(true);
					blood_->SetPos(shot.pos);
					blood_->Emit();
					break;
				}

				// 左前腕
				int LeftHand = MV1SearchFrame(eModelId, "mixamorig:LeftHandMiddle1");
				VECTOR LeftHandPos = MV1GetFramePosition(eModelId, LeftHand);;

				if (IsHitLineSegmentAndOBB(shot.prevPos, shot.pos, leftArmPos, LeftHandPos, 6.0f))
				{
					shot.isAlive = false;
					enemy->Damage(1);

					blood_->SetAlive(true);
					blood_->SetPos(shot.pos);
					blood_->Emit();
					break;
				}

				//右上腕
				int RightArm = MV1SearchFrame(eModelId, "mixamorig:RightArm");
				int RightForeArm = MV1SearchFrame(eModelId, "mixamorig:RightForeArm");
				VECTOR RightArmPos = MV1GetFramePosition(eModelId, RightArm);
				VECTOR RightForeArmPos = MV1GetFramePosition(eModelId, RightForeArm);

				if (IsHitLineSegmentAndOBB(shot.prevPos, shot.pos, RightArmPos, RightForeArmPos, 9.0f))
				{
					shot.isAlive = false;
					enemy->Damage(1);

					blood_->SetAlive(true);
					blood_->SetPos(shot.pos);
					blood_->Emit();
					break;
				}

				// 右前腕1
				int RightHand = MV1SearchFrame(eModelId, "mixamorig:RightHand");
				VECTOR RightHandPos = MV1GetFramePosition(eModelId, RightHand);;

				if (IsHitLineSegmentAndOBB(shot.prevPos, shot.pos, RightArmPos, RightHandPos, 6.0f))
				{
					shot.isAlive = false;
					enemy->Damage(1);

					blood_->SetAlive(true);
					blood_->SetPos(shot.pos);
					blood_->Emit();
					break;
				}

				// 左太もも
				int LeftUpLeg = MV1SearchFrame(eModelId, "mixamorig:LeftUpLeg");
				int LeftLeg = MV1SearchFrame(eModelId, "mixamorig:LeftLeg");
				VECTOR LeftUpLegPos = MV1GetFramePosition(eModelId, LeftUpLeg);
				VECTOR LeftLegPos = MV1GetFramePosition(eModelId, LeftLeg);

				if (IsHitLineSegmentAndOBB(shot.prevPos, shot.pos, LeftUpLegPos, LeftLegPos, 10.0f))
				{
					shot.isAlive = false;
					enemy->Damage(1);

					blood_->SetAlive(true);
					blood_->SetPos(shot.pos);
					blood_->Emit();
					break;
				}

				// 左脛
				int LeftFoot = MV1SearchFrame(eModelId, "mixamorig:LeftFoot");
				VECTOR LeftFootPos = MV1GetFramePosition(eModelId, LeftFoot);;

				if (IsHitLineSegmentAndOBB(shot.prevPos, shot.pos, LeftLegPos, LeftFootPos, 6.0f))
				{
					shot.isAlive = false;
					enemy->Damage(1);

					blood_->SetAlive(true);
					blood_->SetPos(shot.pos);
					blood_->Emit();
					break;
				}

				// 右太もも
				int RightUpLeg = MV1SearchFrame(eModelId, "mixamorig:RightUpLeg");
				int RightLeg = MV1SearchFrame(eModelId, "mixamorig:RightLeg");
				VECTOR RightUpLegPos = MV1GetFramePosition(eModelId, RightUpLeg);
				VECTOR RightLegPos = MV1GetFramePosition(eModelId, RightLeg);

				if (IsHitLineSegmentAndOBB(shot.prevPos, shot.pos, RightUpLegPos, RightLegPos, 10.0f))
				{
					shot.isAlive = false;
					enemy->Damage(1);

					blood_->SetAlive(true);
					blood_->SetPos(shot.pos);
					blood_->Emit();
					break;
				}

				// 右脛
				int RightFoot = MV1SearchFrame(eModelId, "mixamorig:RightFoot");
				VECTOR RightFootPos = MV1GetFramePosition(eModelId, RightFoot);;

				if (IsHitLineSegmentAndOBB(shot.prevPos, shot.pos, RightLegPos, RightFootPos, 6.0f))
				{
					shot.isAlive = false;
					enemy->Damage(1);

					blood_->SetAlive(true);
					blood_->SetPos(shot.pos);
					blood_->Emit();
					break;
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

		MV1CollResultPolyDimTerminate(hitPoly_PShot_S);
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
	VECTOR dir = VSub(movedPos, pos);  // 移動方向ベクトル
	dir = VNorm(dir);             // 正規化（長さを1にする）
	dir = VScale(dir, 100.0f);    // 任意の長さにスケーリング
	VECTOR endPos = VAdd(pos, dir); // pos から伸ばした終点

	// XとY座標をレイの補正値に固定
	pos.y = endPos.y = RAY_COL_Y;

	// 敵とステージの当たり判定設定
	hitPoly_P_S = MV1CollCheck_Line(modelId, -1, pos, endPos, -1);

	//敵とステージが衝突した場合
	if (hitPoly_P_S.HitFlag == 1)
	{
		player_->SetStop(true);	// 停止
		SoundManager::GetInstance()->StopWalk();
	}
	else
	{
		player_->SetStop(false);	// 停止フラグ解除
	}

#ifdef _DEBUG

	isHit_P_S_ = hitPoly_P_S.HitFlag;
#endif // _DEBUG
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
					case ItemBase::TYPE::LIGHT:

						// 救急キットを拾う
						item_->PickLight();

						// アイテムの状態を変更
						item->ChangeState(ItemBase::STATE::PICKUP_L);
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

	// プレイヤーの当たり判定の球体の中心点5
	VECTOR pCenterPos = VAdd(pPos, VGet(0.0f, 110, 0));
	// ドアの当たり判定の球体の中心点
	VECTOR dCenterPos = VAdd(dPos, VGet(0,200, 0));

	float radiusP = 50.0f;
	float radiusD = 210.0f;

	// 中心間の距離
	float dis = VSize(VSub(dCenterPos, pCenterPos));

	// 半径の合計
	float radiusNum = radiusP + radiusD;

	const auto& items = item_->GetItems();


	// ワクチンがすべて拾われているか確認
	if (item_->GetVaccine() == 0)
	{
		// 範囲内にいる状態で
		if (dis < radiusNum)
		{
			isOpenKey_ = true;

			// Fを押したら
			if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_F))
			{
				// ドアが開いた音を再生
				SoundManager::GetInstance()->PlayOpen();
				
				isGameClear_ = true;
			}
		}
		else
		{
			isOpenKey_ = false;
		}
	}
}

bool Collision::GetClear()
{
	return isGameClear_;
}

float Collision::DistanceFromLineSegment(VECTOR A, VECTOR B, VECTOR P)
{
	VECTOR AB = VSub(B, A);
	VECTOR AP = VSub(P, A);
	float ab2 = VDot(AB, AB);
	float ap_ab = VDot(AP, AB);

	float t = ap_ab / ab2;

	if (t < 0.0f) t = 0.0f;
	if (t > 1.0f) t = 1.0f;

	VECTOR closest = VAdd(A, VScale(AB, t));  // 線分上の最近点
	VECTOR diff = VSub(P, closest);

	return VSize(diff);  // 最近点までの距離
}

bool Collision::IsHitLineSegmentAndOBB(const VECTOR& p1, const VECTOR& p2, const VECTOR& top, const VECTOR& bottom, float halfWidth)
{
	VECTOR dir = VSub(p2, p1); // 弾の方向
	VECTOR up = VSub(top, bottom); // 長方形の縦軸
	VECTOR center = VScale(VAdd(top, bottom), 0.5f); // OBB中心
	VECTOR heightDir = VNorm(up);
	VECTOR sideDir = VNorm(VCross(heightDir, VGet(0, 0, 1))); // 横軸（おおよそ）
	VECTOR frontDir = VNorm(VCross(sideDir, heightDir)); // 奥行き軸（補完）

	float halfHeight = VSize(VScale(up, 0.5f));
	float halfDepth = halfWidth; // 奥行きも同じ程度にする（必要なら調整）

	// 3軸
	VECTOR axis[3] = { sideDir, heightDir, frontDir };
	float halfSize[3] = { halfWidth, halfHeight, halfDepth };

	// OBBと線分の交差判定（Separating Axis Theorem）
	VECTOR segCenter = VScale(VAdd(p1, p2), 0.5f);
	VECTOR segDir = VSub(p2, p1);
	float segLen = VSize(segDir) * 0.5f;
	if (segLen < 1e-6f) return false;

	segDir = VNorm(segDir);
	VECTOR diff = VSub(segCenter, center);

	for (int i = 0; i < 3; ++i)
	{
		float r = halfSize[i] + segLen * fabs(VDot(segDir, axis[i]));
		if (fabs(VDot(diff, axis[i])) > r)
			return false;
	}

	return true;
}

void Collision::DrawDebugOBB(const VECTOR& top, const VECTOR& bottom, float halfWidth)
{
	VECTOR up = VSub(top, bottom);
	VECTOR heightDir = VNorm(up);

	// Y軸と up ベクトルの外積から横ベクトルを求める（傾きに強く対応）
	VECTOR sideDir;
	if (fabs(heightDir.x) < 0.0001f && fabs(heightDir.z) < 0.0001f)
	{
		// Y軸と平行な場合、X軸を横とする
		sideDir = VGet(1, 0, 0);
	}
	else
	{
		sideDir = VNorm(VCross(heightDir, VGet(0, 1, 0)));
	}

	VECTOR frontDir = VNorm(VCross(sideDir, heightDir));

	float halfHeight = VSize(VScale(up, 0.5f));
	VECTOR center = VScale(VAdd(top, bottom), 0.5f);

	// OBBの8頂点を計算
	VECTOR corners[8];
	int idx = 0;
	for (int y = -1; y <= 1; y += 2)
	{
		for (int x = -1; x <= 1; x += 2)
		{
			for (int z = -1; z <= 1; z += 2)
			{
				VECTOR offset = VAdd(
					VAdd(VScale(sideDir, x * halfWidth),
						VScale(heightDir, y * halfHeight)),
					VScale(frontDir, z * halfWidth)
				);
				corners[idx++] = VAdd(center, offset);
			}
		}
	}

	int color = GetColor(255, 255, 0); // 黄色
	// 各辺を線でつなぐ（12本）
	const int edges[12][2] = {
		{0,1}, {1,3}, {3,2}, {2,0},
		{4,5}, {5,7}, {7,6}, {6,4},
		{0,4}, {1,5}, {2,6}, {3,7}
	};

	for (int i = 0; i < 12; ++i)
	{
		DrawLine3D(corners[edges[i][0]], corners[edges[i][1]], color);
	}
}
