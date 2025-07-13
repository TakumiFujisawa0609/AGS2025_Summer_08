#include <DxLib.h>
#include "../../Manager/InputManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Common/AnimControl.h"
#include "../../Common/Collision.h"
#include "../../Utility/AsoUtility.h"
#include "../StageBase.h"
#include "../Player.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}


void EnemyBase::Init(TYPE type, int baseModelId, Player* player, StageBase* stage)
{
	// 敵種別
	type_ = type;

	// ゲームシーン内のplayerを取得
	player_ = player;

	stage_ = stage;

	// 敵モデル描画
	modelId_ = MV1DuplicateModel(baseModelId);

	// モデルのコリジョン情報の初期化
	MV1SetupCollInfo(modelId_, -1);	// コリジョン情報の初期化

	// アニメーションクラスの生成と初期化
	anim_ = new AnimControl();
	anim_->Init(modelId_);

	// 敵初期位置
	pos_ = INIT_ENEMY_POS;

	// 敵初期角度
	angle_ = INIT_ENEMY_ANGLE;

	// 敵モデルの座標設定
	MV1SetPosition(modelId_, pos_);

	// 初期状態
	ChangeState(STATE::IDLE);

	// 敵の移動限界フラグ
	isStop_ = false;
	// 敵の生存フラグ
	isAlive_ = true;

	// パラメータ設定
	SetParam();
}

void EnemyBase::Update()
{
	// プレイヤーとの距離を更新
	LookPlayer();

	// 状態に応じた行動（追尾・攻撃など）
	// 生きているときだけ状態変更を行う
	if (isAlive_)
	{
		ChangeStateDist();
	}

	switch (state_) {
	case STATE::IDLE:
		UpdateIdle();
		break;
	case STATE::WALK:
		UpdateWalk();
		break;
	case STATE::RUN:
		UpdateRun();
		break;
	case STATE::ATTACK:
		UpdateAttack();
		break;
	case STATE::DIE:
		UpdateDie();
		break;
	}

	// 視認判定
	isPlayerVisible_ = CanSeePlayer();

	// プレイヤーが見えていたら
	if (isPlayerVisible_) {
		lastSeenPlayerPos_ = player_->GetPPos();
		hasLastSeen_ = true;
	}

	// 位置と向きを反映する
	MV1SetPosition(modelId_, pos_);
	MV1SetRotationXYZ(modelId_, angle_);

	// アニメーションの時間更新
	anim_->Update();
}

void EnemyBase::Draw()
{
	switch (state_) {
	case STATE::IDLE:
		DrawIdle();
		break;
	case STATE::WALK:
		DrawWalk();
		break;
	case STATE::RUN:
		DrawRun();
		break;
	case STATE::ATTACK:
		DrawAttack();
		break;
	case STATE::DIE:
		DrawDie();
		break;
	}


	// 敵の当たり判定用中心
	VECTOR centerPosE = VAdd(pos_, VGet(0, 100, 0));

	float dis = VSize(VSub(centerPosE, player_->GetPPos()));

	// 範囲内判定
	if (dis < 2400)
	{
		// 敵モデル描画
		MV1DrawModel(modelId_);
	}

#ifdef DEBUG
	//VECTOR centerPos = pos_;
//centerPos = VAdd(centerPos, VGet(0, 100, 0));

//DrawSphere3D(centerPos, 60, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);


#endif // DEBUG
}

void EnemyBase::Release()
{
	anim_->Release();	// アニメーションクラスの解放処理
	delete anim_;	    // メモリ解放

	// 敵モデル解放
	MV1DeleteModel(modelId_);
}

void EnemyBase::LookPlayer()
{
	// プレイヤーの座標を取得
	VECTOR target = player_->GetPPos();
	// プレイヤーが見えているならその位置を追尾
	target = isPlayerVisible_ ? player_->GetPPos() : lastSeenPlayerPos_;

	// 移動方向を計算する（プレイヤー座標 - 敵座標）
	moveDir_ = VSub(target, pos_);

	// 移動方向のベクトルサイズを取得
	dist_ = VSize(moveDir_);

	// 移動方向を正規化する
	moveDir_ = VNorm(moveDir_);
}

// プレイヤー追尾
void EnemyBase::ChasePlayer()
{
	// 移動方向がゼロベクトルでない場合
	if (!AsoUtility::EqualsVZero(moveDir_))
	{
		// 移動量を計算する（向き * スピード）
		VECTOR movePow = VScale(moveDir_, speed_);

		// 移動処理（座標＋移動量)
		pos_ = VAdd(pos_, movePow);

		// 方向から角度(ラジアン）に変換する
		angle_.y = atan2(moveDir_.x, moveDir_.z);

		// モデルの方向が生の不の方向を向いてるので、補正する
		angle_.y += AsoUtility::Deg2RadF(180.0f);
	}
}

// 状態を切り替える
void EnemyBase::ChangeState(STATE state)
{
	// 死亡後に他の状態に変更しないようブロック
	if (!isAlive_ && state != STATE::DIE) return;

	state_ = state;

	switch (state_) {
	case STATE::IDLE:
		ChangeIdle();
		break;
	case STATE::WALK:
		ChangeWalk();
		break;
	case STATE::RUN:
		ChangeRun();
		break;
	case STATE::ATTACK:
		ChangeAttack();
		break;
	case STATE::DIE:
		ChangeDie();
		break;
	}
}

void EnemyBase::ChangeStateDist()
{
	// プレイヤーが死んでいたら常にIDLEにする
	if (!player_->GetAlive())
	{
		ChangeState(STATE::IDLE);
		return;
	}

	// 視認できない上に到達済みならIDLEに戻る
	if (!isPlayerVisible_ && hasLastSeen_ && dist_ < RUN_DISTANCE)
	{
		hasLastSeen_ = false;
		ChangeState(STATE::IDLE);
		return;
	}

	// 状態を切り替える距離
	if (isPlayerVisible_ && dist_ < ATTACK_DISTANCE)
	{
		ChangeState(STATE::ATTACK);
	}
	else if (dist_ < RUN_DISTANCE)
	{
		ChangeState(STATE::RUN);
	}
	//else if (dist_ < WALK_DISTANCE)
	//{
	//	ChangeState(STATE::WALK);
	//}
	else if (dist_ > RUN_DISTANCE)
	{
		ChangeState(STATE::IDLE);
	}
}

bool EnemyBase::GetAlive()
{
	return isAlive_;
}

void EnemyBase::SetAlive(bool isAlive)
{
	isAlive_ = isAlive;

	if (!isAlive_)
	{
		ChangeState(STATE::DIE);  // 死亡状態に変える
		speed_ = 0.0f;       // 止めるなど
	}
}

EnemyBase::STATE EnemyBase::GetState() const
{
	return state_;
}

float EnemyBase::GetAnimRate()
{
	return anim_->GetCurrentAnimRate();
}

VECTOR EnemyBase::GetMoveDir() const
{
	return moveDir_;
}

// プレイヤーが視認できるか
bool EnemyBase::CanSeePlayer()
{
	VECTOR start = VAdd(pos_, VGet(0, 100, 0));      // 敵の目線位置
	VECTOR end = VAdd(player_->GetPPos(), VGet(0, 100, 0)); // プレイヤー目線位置

	int sModelId = stage_->GetModelId();

	// レイキャストでステージとの当たりを調べる
	MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(sModelId, -1, start, end);

	// ヒットしなければ → 遮る壁がない → 見えている
	return result.HitFlag == 0;
}

int EnemyBase::GetModelId() const
{
	return modelId_;
}

VECTOR EnemyBase::GetPos() const
{
	return pos_;
}

void EnemyBase::SetPos(VECTOR pos)
{
	pos_ = pos;	// 敵座標をセット
}

void EnemyBase::SetStop(bool isStop)
{
	isStop_ = isStop;	// 停止フラグをセット
}

void EnemyBase::Damage(int damage)
{
	// ダメージを受ける
	hp_ -= damage;

	SceneManager::GetInstance()->SetHitShotCnt(1);

	// hpが０になったら死亡状態に
	if (hp_ <= 0)
	{
		ChangeState(STATE::DIE);

		hp_ = 0; // hpを０に固定

		isAlive_ = false; // 生存フラグをfalseにする

		SoundManager::GetInstance()->PlayKill();
	}
}

void EnemyBase::ChangeIdle(void)
{
	// アニメ再生
	anim_->Play(ANIM_IDLE, 1);

	speed_ = 0.0f;
}

void EnemyBase::ChangeWalk(void)
{
	//アニメ再生
	anim_->Play(ANIM_WALK, 1);

	speed_ = MOVE_WALK_SPEED;  // 歩き速度
}

void EnemyBase::ChangeRun(void)
{
	// アニメ再生
	anim_->Play(ANIM_RUN, 1);

	speed_ = MOVE_RUN_SPEED; // 走り速度

	// 再生済みでなければ再生
	if (!hasPlayedRunSound_)
	{
		SoundManager::GetInstance()->PlayVoice(pos_);
		hasPlayedRunSound_ = true;
	}
}

void EnemyBase::ChangeAttack(void)
{
	// アニメ再生
	anim_->Play(ANIM_ATTACK, 2.2f);

	speed_ = 0.0f;
}

void EnemyBase::ChangeDie(void)
{
	// アニメ再生
	anim_->Play(ANIM_DIE, 1);

	speed_ = 0.0f;

	// 死亡時の処理
	SoundManager::GetInstance()->StopVoice();

	// キルカウント加算
	SceneManager::GetInstance()->SetKillEnemyCnt(1);
}

void EnemyBase::UpdateIdle(void)
{
}

void EnemyBase::UpdateWalk(void)
{
	ChasePlayer();
}

void EnemyBase::UpdateRun(void)
{
	if (dist_ < 3.0f) {
		ChangeState(STATE::IDLE);
		return;
	}
	ChasePlayer();
}

void EnemyBase::UpdateAttack(void)
{
}

void EnemyBase::UpdateDie(void)
{

}

void EnemyBase::DrawIdle(void)
{
}

void EnemyBase::DrawWalk(void)
{
}

void EnemyBase::DrawRun(void)
{
}

void EnemyBase::DrawAttack(void)
{
}

void EnemyBase::DrawDie(void)
{
}