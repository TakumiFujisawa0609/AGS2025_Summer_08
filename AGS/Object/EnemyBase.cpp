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
	// 敵初期角度
	angle_ = INIT_ENEMY_ANGLE;

	// 敵モデルの座標設定
	MV1SetPosition(modelId_, pos_);

	// 初期アニメーション設定
	anim_->Play(ANIM_IDLE);
}

void EnemyBase::Update()
{


	if (InputManager::GetInstance()->IsTrgDown(KEY_INPUT_1)) { state_ = STATE_IDLE; }	// 待機
	if (InputManager::GetInstance()->IsTrgDown(KEY_INPUT_2)) { state_ = STATE_WALK; }	// 歩き
	if (InputManager::GetInstance()->IsTrgDown(KEY_INPUT_3)) { state_ = STATE_RUN; }	// 走り
	if (InputManager::GetInstance()->IsTrgDown(KEY_INPUT_4)) { state_ = STATE_ATTACK; }	// 攻撃
	if (InputManager::GetInstance()->IsTrgDown(KEY_INPUT_5)) { state_ = STATE_DIE; }	// 死亡

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

		// 移動量を計算する（移動 * スピード）
		VECTOR movePow = VScale(moveDir, speed_);
		// 移動処理（座標＋移動量)
		pos_ = VAdd(pos_, movePow);

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
	

	MV1SetPosition(modelId_, pos_);
	MV1SetRotationXYZ(modelId_, angle_);

}
