#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Manager/Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Utility/AsoUtility.h"
#include "../Object/Player.h"

void Player::Init(void)
{
	movedPos_ = { 0.0f, 0.0f, 0.0f };
	pos_ = { 0.0f, 0.0f, 0.0f };
	MV1SetPosition(modelId_, pos_);

	// 移動ベクトル初期化
	moveVec_ = AsoUtility::VECTOR_ZERO;

	// モデルの角度設定
	rot_ = { 0.0f, 0.0f, 0.0f };
	// モデルの角度
	localRot_ = INIT_MODEL_ROT_OFFSET;

	// カメラアングル
	cameraAngle_ = { 0.0f, 0.0f, 0.0f };

	// 体力初期化
	hp_ = DEFAULT_HP;

	// 回復可能数
	heal_ = 0;
	isHeal_ = false;

	isStop_ = false;

	isAlive_ = true;
}

void Player::Update(VECTOR angle)
{
	// カメラアングル取得
	cameraAngle_ = angle;

	// 移動処理
	ProcessMove(cameraAngle_);
	//SetRotation();

	// HP
	Hp();

	// ダメージ表現
	DamageEffect();


	if (CheckHitKey(KEY_INPUT_0)) { isAlive_ = false; }
}

void Player::Draw(void)
{
	//VECTOR startPos = VAdd(playerPos_, VGet(0.0f, 30.0f, 0));                          // 敵の座標
	//VECTOR endPos = VAdd(playerPos_, VGet(0.0f, 160.0f, 0));  // カプセルの上端（高さ60の例）
	//float radius = 45.0f;	// 半径45（調整可）

	//VECTOR centerPos = VAdd(pos_, VGet(0.0f, 110, 0));

	//DrawSphere3D(centerPos, radius, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);	// 球を描画

	// プレイヤー座標
	DrawFormatString(0, 40, 0xffffff, "playerPos:(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);

	//DrawFormatString(0, 700, 0xffffff, "isStop_P:%d", isStop_);
	//DrawFormatString(0, 740, 0xffffff, "isAlive_P:%d", isAlive_);
	//
	//DrawFormatString(500, 0, 0xffffff, "%d", hp_);

}

void Player::Release(void)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// HP
void Player::Hp(void)
{
	static float holdTime = 0.0f;
	float deltaTime = SceneManager::GetInstance()->GetDeltaTime();

	// 死亡処理
	if (hp_ == 0)
	{
		isStop_ = true;
		isAlive_ = false;

		SoundManager::GetInstance()->StopWalk();
	}

	// HP最大制限
	if (hp_ >= DEFAULT_HP)
		hp_ = DEFAULT_HP;

	// Qキーを押した瞬間
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_Q) && heal_ > 0 && hp_ < DEFAULT_HP)
	{
		isHoldingQ_ = true;
		holdTime = 0.0f;

		isHeal_ = false;
	}

	// Qキーを離した瞬間
	if (InputManager::GetInstance().IsTrgUp(KEY_INPUT_Q))
	{
		isHoldingQ_ = false;
		holdTime = 0.0f;

		SoundManager::GetInstance()->StopHeal();
	}

	// Qを押し続けている間は時間を加算
	if (isHoldingQ_)
	{
		SoundManager::GetInstance()->PlayHeal();
		holdTime += deltaTime;

		if (holdTime >= 2.0f)
		{
			hp_ += 1;
			heal_ -= 1;

			SoundManager::GetInstance()->PlayHeal();
			SoundManager::GetInstance()->PlayHealVoice();

			isHeal_ = true;

			// リセット
			isHoldingQ_ = false;
			holdTime = 0.0f;
		}
	}
}

void Player::ModelReflect()
{
	// 進んでよかったら
	if (!isStop_)
	{
		pos_ = movedPos_;
	}

	MV1SetPosition(modelId_, pos_);
}

void Player::Damage(int damage)
{
	// ダメージを受ける
	hp_ -= damage;

	// 体力が0になったら0に固定
	if (hp_ <= 0)
	{ 
		hp_ = 0; 
		SoundManager::GetInstance()->PlayDie();
	}
	else if (hp_ == 1)
	{
		SoundManager::GetInstance()->PlayHit();
	}
}

void Player::DamageEffect()
{

}

void Player::SetStop(bool isStop)
{
	isStop_ = isStop;
}

// 回復可能数
void Player::Heal(int heal)
{
	heal_ += heal;
}
																	
VECTOR Player::GetPPos(void)
{
	return pos_;
}

VECTOR Player::GetMovedPos(void)
{
	return movedPos_;
}

bool Player::GetAlive(void)
{
	return isAlive_;
}

int Player::GetHp()
{
	return hp_;
}

int Player::GetHeal()
{
	return heal_;
}

// 回転設定
void Player::SetRotation(void)
{
	// 回転行列を使用した角度設定
	// ---------------------------
	// 単位行列を設定する
	MATRIX mat = MGetIdent();

	// モデル自体のY軸回転行列を作成する
	MATRIX mGetRotY = MGetRotY(rot_.y);

	// モデルの補正用Y軸回転行列を作成する
	MATRIX mGetLocalRotY = MGetRotY(localRot_.y);

	// 行列を合成
	mat = MMult(mat, mGetRotY);
	mat = MMult(mat, mGetLocalRotY);

	// 行列を使用してモデルの角度を設定
	MV1SetRotationMatrix(modelId_, mat);
}

// 移動処理
void Player::ProcessMove(VECTOR angle)
{
	// 移動方向を決める
	moveVec_ = AsoUtility::VECTOR_ZERO;
	if (InputManager::GetInstance().IsNew(KEY_INPUT_S)) {
		moveVec_ = VAdd(moveVec_, AsoUtility::DIR_F);
		SoundManager::GetInstance()->PlayWalk();
	}
	if (InputManager::GetInstance().IsNew(KEY_INPUT_W)) { 
		moveVec_ = VAdd(moveVec_, AsoUtility::DIR_B);
		SoundManager::GetInstance()->PlayWalk();
	}
	if (InputManager::GetInstance().IsNew(KEY_INPUT_A)) {
		moveVec_ = VAdd(moveVec_, AsoUtility::DIR_R);
		SoundManager::GetInstance()->PlayWalk();
	}
	if (InputManager::GetInstance().IsNew(KEY_INPUT_D)) { 
		moveVec_ = VAdd(moveVec_, AsoUtility::DIR_L); 
		SoundManager::GetInstance()->PlayWalk();
	}
	if (!CheckHitKey(KEY_INPUT_W) && !CheckHitKey(KEY_INPUT_A) &&
		!CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D)) {
		SoundManager::GetInstance()->StopWalk();
	}

	// 移動処理
	// 動いていたら
	if (!AsoUtility::EqualsVZero(moveVec_))
	{
		// カメラ角度分設定する
		MATRIX cameraMatY = MGetRotY(angle.y);
		moveVec_ = VTransform(moveVec_, cameraMatY);

		// 座標更新
		moveVec_ = VNorm(moveVec_);

		// Q長押し中は半分の速度
		float speed = isHoldingQ_ ? MOVE_SPEED * 0.5f : MOVE_SPEED;
		moveVec_ = VScale(moveVec_, speed);

		// 移動予定位置に移動処理を代入
		movedPos_ = VAdd(pos_, moveVec_); 

		// 方向を角度に変換する(XZ平面　Y軸)
		moveVecRad_.y = atan2f(moveVec_.x, moveVec_.z);

		// 計算角度を設定
		rot_.y = moveVecRad_.y;
	}
}



