#include <DxLib.h>
#include "../Object/Player.h"

void Player::Init(void)
{
	playerPos_ = { 0.0f, 0.0f, 0.0f };
}

void Player::Update(void)
{
	if (CheckHitKey(KEY_INPUT_W)) playerPos_.z += 10.0f;
	if (CheckHitKey(KEY_INPUT_S)) playerPos_.z -= 10.0f;
	if (CheckHitKey(KEY_INPUT_A)) playerPos_.x -= 10.0f;
	if (CheckHitKey(KEY_INPUT_D)) playerPos_.x += 10.0f;
	if (CheckHitKey(KEY_INPUT_UP)) playerPos_.y += 10.0f;
	if (CheckHitKey(KEY_INPUT_DOWN)) playerPos_.y -= 10.0f;
}

void Player::Draw(void)
{

	// 各方向への半分のサイズ
	float halfSizeX = 60.0f;
	float halfSizeY = 120.0f;
	float halfSizeZ = 60.0f;

	// 直方体の対角2点を計算
	VECTOR pos1 = VGet(
		playerPos_.x - halfSizeX,
		playerPos_.y - halfSizeY,
		playerPos_.z - halfSizeZ
	);

	VECTOR pos2 = VGet(
		playerPos_.x + halfSizeX,
		playerPos_.y + halfSizeY,
		playerPos_.z + halfSizeZ
	);

	// 長方形
	DrawCube3D(pos1, pos2, 0x0000ff, 0x0000ff, false);

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



