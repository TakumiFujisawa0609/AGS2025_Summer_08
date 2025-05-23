#include <DxLib.h>
#include "../Object/Player.h"

void Player::Init(void)
{
	playerPos_ = { 0.0f, 0.0f, 0.0f };
}

void Player::Update(void)
{
	if (CheckHitKey(KEY_INPUT_W)) playerPos_.z += 4.0f;
	if (CheckHitKey(KEY_INPUT_S)) playerPos_.z -= 4.0f;
	if (CheckHitKey(KEY_INPUT_A)) playerPos_.x -= 4.0f;
	if (CheckHitKey(KEY_INPUT_D)) playerPos_.x += 4.0f;
	/*if (CheckHitKey(KEY_INPUT_UP)) playerPos_.y += 10.0f;
	if (CheckHitKey(KEY_INPUT_DOWN)) playerPos_.y -= 10.0f;*/
}

void Player::Draw(void)
{

	//VECTOR startPos = VAdd(playerPos_, VGet(0.0f, 30.0f, 0));                          // 敵の座標
	//VECTOR endPos = VAdd(playerPos_, VGet(0.0f, 160.0f, 0));  // カプセルの上端（高さ60の例）
	float radius = 45.0f;	// 半径30（調整可）

	VECTOR centerPos = VAdd(playerPos_, VGet(0.0f, 110, 0));


	// キューブ描画
	//DrawCapsule3D(startPos, endPos, radius, 8, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);  // ワイヤーフレーム表示

	DrawSphere3D(centerPos, radius, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);	// 球を描画

	// プレイヤー座標
	DrawFormatString(0, 40, 0xffffff, "playerPos:(%.2f, %.2f, %.2f)", playerPos_.x, playerPos_.y, playerPos_.z);
}

void Player::Release(void)
{
	
}

VECTOR Player::GetPPos(void)
{
	return playerPos_;
}



