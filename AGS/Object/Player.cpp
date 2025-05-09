#include <DxLib.h>
#include "../Object/Player.h"

void Player::Init(void)
{
	playerPos_ = { 0.0f, 0.0f, 0.0f };
}

void Player::Update(void)
{
	/*if (CheckHitKey(KEY_INPUT_W)) playerPos_.z += 20.0f;
	if (CheckHitKey(KEY_INPUT_S)) playerPos_.z -= 20.0f;
	if (CheckHitKey(KEY_INPUT_A)) playerPos_.x += 20.0f;
	if (CheckHitKey(KEY_INPUT_D)) playerPos_.x -= 20.0f;
	if (CheckHitKey(KEY_INPUT_UP)) playerPos_.y += 20.0f;
	if (CheckHitKey(KEY_INPUT_DOWN)) playerPos_.y += 20.0f;*/
}

void Player::Draw(void)
{
	// プレイヤーの当たり判定用球体の描画
	DrawSphere3D(playerPos_, 80.0f, 10.0f, 0x0000ff, 0x0000ff, false);
}

void Player::Release(void)
{

}

VECTOR Player::GetPPos(void)
{
	return playerPos_;
}



