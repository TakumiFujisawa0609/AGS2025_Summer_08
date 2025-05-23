#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Common/AnimControl.h"
#include "../Common/Collision.h"
#include "../Utility/AsoUtility.h"
#include "Player.h"
#include "EnemyBase.h"

void EnemyBase::Init(Player* player)
{
	player_ = player;	// ゲームシーン内のプレイヤーポインタを取得

	// 敵モデル描画
	modelId_ = MV1LoadModel("Data/Model/Enemy/Zombie.mv1");

	// モデルのコリジョン情報の初期化
	MV1SetupCollInfo(modelId_, 0, 2, 2, 2);	// コリジョン情報の初期化

	// アニメーションクラスの生成と初期化
	anim_ = new AnimControl();
	anim_->Init(modelId_);

	// 敵初期位置
	pos_ = INIT_ENEMY_POS;
	// 移動予定位置初期化
	movedPos_ = INIT_ENEMY_POS;

	// 敵初期角度
	angle_ = INIT_ENEMY_ANGLE;

	// 敵モデルの座標設定
	MV1SetPosition(modelId_, pos_);

	// 初期アニメーション設定
	anim_->Play(ANIM_IDLE, 1);

	// 敵の移動限界フラグ
	isStop_ = false;	// 停止フラグ


}

void EnemyBase::Update()
{

	// プレイヤー追尾
	ChacePlayer();

	// アニメーション切り替え
	ChangeAnim();

	// アニメーションの時間更新
	anim_->Update();
	
}

void EnemyBase::Draw()
{
	// 敵モデル描画
	MV1DrawModel(modelId_);

	// デバッグ
	DrawFormatString(0, 20, 0xffffff, "enemyPos : (%f, %f, %f)", pos_.x, pos_.y, pos_.z);
	DrawFormatString(0, 80, 0xffffff, "dist : %f", dist_);
	DrawFormatString(0, 140, 0xffffff, "isStop:%d", isStop_);

	float radius = 45.0f;               // 半径30（調整可）
	VECTOR centerPos = VAdd(pos_, VGet(0.0f, 110, 0));	// 敵の衝突用中心座標

	//DrawSphere3D(centerPos, radius, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
	

	int animIndex = MV1GetAttachAnim(modelId_, 0);  // 敵の0番目のアニメ
	float blendRate = MV1GetAttachAnimBlendRate(modelId_, animIndex);
	DrawFormatString(0, 280, GetColor(255, 255, 0), "BlendRate : %.2f", blendRate);


}

void EnemyBase::Release()
{
	anim_->Release();	// アニメーションクラスの解放処理
	delete anim_;	    // メモリ解放

	// 敵モデル解放
	MV1DeleteModel(modelId_);
}



void EnemyBase::ChangeAnim()
{
	// 状態に応じてアニメーションを切り替える
	switch (state_) {
	case STATE_IDLE:
		anim_->Play(ANIM_IDLE, 1);
		break;
	case STATE_WALK:
		anim_->Play(ANIM_WALK, 1);
		break;
	case STATE_RUN:
		anim_->Play(ANIM_RUN, 1);
		break;
	case STATE_ATTACK:
		anim_->Play(ANIM_ATTACK, 1.5f);
		break;
	case STATE_DIE:
		anim_->Play(ANIM_DIE, 1);
		break;
	}
}

// プレイヤー追尾
void EnemyBase::ChacePlayer()
{
	// プレイヤーの座標を取得
	VECTOR pPos = player_->GetPPos();

	// 移動方向を計算する（プレイヤー座標 - 敵座標）
	VECTOR moveDir = VSub(pPos, pos_);
	
	// 移動方向のベクトルサイズを取得
	dist_ = VSize(moveDir);

	// 移動方向を正規化する
	moveDir = VNorm(moveDir);


	// スピード設定
	if (state_ == STATE_WALK) speed_ = MOVE_WALK_SPEED;  // 歩き速度
	else if (state_ == STATE_RUN) speed_ = MOVE_RUN_SPEED; // 走り速度
	else speed_ = 0.0f; // それ以外なら止まる

	// 移動方向がゼロベクトルでない場合
	if (!AsoUtility::EqualsVZero(moveDir))
	{
		// 移動量を計算する（向き * スピード）
		VECTOR movePow = VScale(moveDir, speed_);

		// 移動処理（座標＋移動量)
		movedPos_ = VAdd(pos_, movePow);	// ←移動予定位置

		if (!isStop_)
		{
			pos_ = movedPos_;
		}

		// 方向から角度(ラジアン）に変換する
		angle_.y = atan2(moveDir.x, moveDir.z);

		// モデルの方向が生の不の方向を向いてるので、補正する
		angle_.y += AsoUtility::Deg2RadF(180.0f);
	}
	
	// アニメーションを切り替える距離
	if (dist_ < ATTACK_DISTANCE)
	{
		state_ = STATE_ATTACK;
	}
	else if (dist_ < RUN_DISTANCE)
	{
		state_ = STATE_RUN;
	}
	else if (dist_ < WALK_DISTANCE)
	{
		state_ = STATE_WALK;
	}
	else
	{
		state_ = STATE_IDLE;
	}
	
	// 
	MV1SetPosition(modelId_, pos_);
	MV1SetRotationXYZ(modelId_, angle_);

}

int EnemyBase::GetModelId() const
{
	return modelId_;
}

VECTOR EnemyBase::GetPos() const
{
	return pos_;
}

VECTOR EnemyBase::GetMovedPos() const
{
	return movedPos_;
}

void EnemyBase::SetPos(VECTOR pos)
{
	pos_ = pos;	// 敵座標をセット
}

void EnemyBase::SetStop(bool isStop)
{
	isStop_ = isStop;	// 停止フラグをセット
	
}