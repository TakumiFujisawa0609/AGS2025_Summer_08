#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"
#include "../Object/Player.h"

void Player::Init(void)
{
	pos_ = { 0.0f, 0.0f, 0.0f };
}

void Player::Update(void)
{
	Move();
}

void Player::Draw(void)
{

	//VECTOR startPos = VAdd(playerPos_, VGet(0.0f, 30.0f, 0));                          // 敵の座標
	//VECTOR endPos = VAdd(playerPos_, VGet(0.0f, 160.0f, 0));  // カプセルの上端（高さ60の例）
	float radius = 45.0f;	// 半径30（調整可）

	VECTOR centerPos = VAdd(pos_, VGet(0.0f, 110, 0));


	// キューブ描画
	//DrawCapsule3D(startPos, endPos, radius, 8, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);  // ワイヤーフレーム表示

	DrawSphere3D(centerPos, radius, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);	// 球を描画

	// プレイヤー座標
	DrawFormatString(0, 40, 0xffffff, "playerPos:(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
}

void Player::Release(void)
{
	
}

void Player::Dir()
{

}

void Player::Move()
{
	// カメラの移動
	// 移動方向を決める
	moveDir_ = AsoUtility::VECTOR_ZERO;
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_W)) { moveDir_ = VAdd(moveDir_, AsoUtility::DIR_F); }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_S)) { moveDir_ = VAdd(moveDir_, AsoUtility::DIR_B); }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_D)) { moveDir_ = VAdd(moveDir_, AsoUtility::DIR_R); }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_A)) { moveDir_ = VAdd(moveDir_, AsoUtility::DIR_L); }

	

	// 移動処理
	// 動いていなかったら
	if (!AsoUtility::EqualsVZero(moveDir_))
	{
		// 移動量を計算する（移動 * スピード）
		VECTOR movePow = VScale(moveDir_, MOVE_SPEED);
		// 移動処理（座標＋移動量)
		pos_ = VAdd(pos_, movePow);
		// 移動方向を正規化する
		moveDir_ = VNorm(moveDir_);

		//// 方向から角度(ラジアン）に変換する
		//angle_.y = atan2(moveDir.x, moveDir.z);
		//// モデルの方向が生の不の方向を向いてるので、補正する
		//angle_.y += AsoUtility::Deg2RadF(180.0f);
	}

	MV1SetPosition(modelId_, pos_);
	//MV1SetRotationXYZ(modelId_, angles_);
}

VECTOR Player::GetPPos(void)
{
	return pos_;
}



