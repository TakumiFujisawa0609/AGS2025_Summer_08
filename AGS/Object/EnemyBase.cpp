#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"
#include "Player.h"
#include "EnemyBase.h"

void EnemyBase::Init(Player* player)
{
	player_ = player;	// ゲームシーン内のプレイヤーポインタを取得

	// 敵モデル描画
	modelId_ = MV1LoadModel("Data/Model/Enemy/Zombie.mv1");

	// アニメーションクラスの生成と初期化
	anim_ = new AnimControl();
	anim_->Init(modelId_);

	// 敵初期位置
	pos_ = INIT_ENEMY_POS;
	// 移動予定位置初期化
	nextPos_ = INIT_ENEMY_POS;

	// 敵初期角度
	angle_ = INIT_ENEMY_ANGLE;

	// 敵モデルの座標設定
	MV1SetPosition(modelId_, pos_);

	// 初期アニメーション設定
	anim_->Play(ANIM_IDLE);

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
}

void EnemyBase::Release()
{
	anim_->Release();	// アニメーションクラスの解放処理
	delete anim_;	    // メモリ解放

	// 敵モデル解放
	MV1DeleteModel(modelId_);
}

int EnemyBase::GetModelId()
{
	return modelId_;
}

VECTOR EnemyBase::GetPos()
{
	return pos_;
}

VECTOR EnemyBase::GetNextPos()
{
	return nextPos_;
}

void EnemyBase::SetIsStop(bool isStop)
{
	isStop_ = isStop;	// 停止フラグをセット
}

void EnemyBase::ChangeAnim()
{
	// 状態に応じてアニメーションを切り替える
	switch (state_) {
	case STATE_IDLE:
		anim_->Play(ANIM_IDLE);
		break;
	case STATE_WALK:
		anim_->Play(ANIM_WALK);
		break;
	case STATE_RUN:
		anim_->Play(ANIM_RUN);
		break;
	case STATE_ATTACK:
		anim_->Play(ANIM_ATTACK);
		break;
	case STATE_DIE:
		anim_->Play(ANIM_DIE);
		break;
	}
}

void EnemyBase::ChacePlayer()
{
	VECTOR pPos = player_->GetPPos();	// プレイヤーの座標を取得

	// 移動方向を計算する（プレイヤー座標 - 敵座標）
	VECTOR moveDir = VSub(pPos, pos_);
	

	// プレイヤーとの距離を計算
	dist_ = VSize(moveDir);

	// 移動方向を正規化する
	moveDir = VNorm(moveDir);

	// スピード設定
	if (state_ == STATE_WALK) speed_ = MOVE_WALK_SPEED;  // 歩き速度
	else if (state_ == STATE_RUN) speed_ = MOVE_RUN_SPEED; // 走り速度
	else speed_ = 0.0f; // それ以外なら止まる

	if (!AsoUtility::EqualsVZero(moveDir))
	{
		// 移動量を計算する（向き * スピード）
		VECTOR movePow = VScale(moveDir, speed_);
		// 移動処理（座標＋移動量)
		nextPos_ = VAdd(pos_, movePow);	// ←移動予定位置


		// 方向から角度(ラジアン）に変換する
		angle_.y = atan2(moveDir.x, moveDir.z);

		// モデルの方向が生の不の方向を向いてるので、補正する
		angle_.y += AsoUtility::Deg2RadF(180.0f);

		// ストップフラグが立っていなければ移動する
		//if (!isStop_)
		//{
			pos_ = nextPos_;	// 敵座標を更新
		//}


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
	

	MV1SetPosition(modelId_, pos_);
	MV1SetRotationXYZ(modelId_, angle_);

}
