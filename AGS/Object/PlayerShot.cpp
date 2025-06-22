#include <DxLib.h>
#include "../Object/Camera.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"
#include "PlayerShot.h"

PlayerShot::PlayerShot()
{
}

PlayerShot::~PlayerShot()
{
}

void PlayerShot::Init(Camera* camera)
{
	camera_ = camera;

	// モデルロード
	//modelId_ = MV1LoadModel("Data/Model/bullet/bullet.mv1");

	image_ = LoadGraph("Data/Image/bulletImage.png");

	pos_ = DEFAULT_POS;
	startPos_ = DEFAULT_POS;
	dir_ = { 0,0,0 };
	scale_ = DEFAULT_SCALE;

	ammo_ = MAX_AMMO;

	isAlive_ = false;

	magazine_ = 0;

	MV1SetScale(modelId_, scale_);
}

void PlayerShot::Update(void)
{
	// 弾発射
	Shot();

	// リロード
	ReLoad();
}

void PlayerShot::Draw(void)
{
	//if(isAlive_) MV1DrawModel(modelId_);

	if(isAlive_) DrawSphere3D(pos_, 10, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
	DrawFormatString(0, 540, 0xffffff, "isShotAlive:%d", isAlive_ );
	DrawFormatString(0, 560, 0xffffff, "magazine_:%d", magazine_);
	//DrawFormatString(0, 500, 0xffffff, "ShotPos:(%f,%f,%f)", pos_.x, pos_.y, pos_.z);
	//DrawFormatString(0, 520, 0xffffff, "dir_: (%.2f, %.2f, %.2f)", dir_.x, dir_.y, dir_.z);
	//DrawFormatString(0, 560, 0xffffff, "Dist:%f", dist_);


	// 表示座標
	int x = 130;
	int y = 990;
	int white = GetColor(255, 255, 255);

	// 弾数が1桁かどうかで座標調整
	int ammoOffsetX = (ammo_ < 10) ? 16 : 0;  // 1桁なら少し右へ
	int maxOffsetX = (MAX_AMMO < 10) ? 12 : 0; // 最大弾数側にも必要なら調整

	SetFontSize(32);
	// 残弾・スラッシュ・最大弾数を縦に表示、少しずらして描画
	DrawFormatString(x - 34 + ammoOffsetX, y + 0, white, "%d", ammo_); // 残弾
	SetFontSize(55);
	DrawString(x, y, "/", white);   // スラッシュ
	SetFontSize(32);
	DrawFormatString(x + 22 + maxOffsetX, y + 25, white, "%d", MAX_AMMO); // 最大弾数

	float scale = 0.07f;  // 縮小
	DrawRotaGraph(60, 1020, scale, 0.0f, image_, true);
}

void PlayerShot::Release(void)
{
	MV1DeleteModel(modelId_);
}

void PlayerShot::Shot(void)
{
	// 弾発射
	if (!isAlive_
		&& InputManager::GetInstance()->IsTrgDown(MOUSE_INPUT_LEFT)
		&& ammo_ > 0)
	{
		// カメラ位置と方向取得→発射位置に設定
		startPos_ = pos_ = camera_->GetPos();
		// 正規化して向きを取得（符号反転して前に飛ばす）
		dir_ = VScale(VNorm(camera_->GetForward()), -1.0f);

		// 生存フラグ立てる
		isAlive_ = true;

		// 弾数を減らす
		ammo_--;

		SoundManager::GetInstance()->PlayShot();
	}

	// 弾移動
	if (isAlive_)
	{
		// 前に進む
		pos_ = VAdd(pos_, VScale(dir_, SHOT_SPEED));

		// 発射地点との距離を計算
		dist_ = VSize(VSub(pos_, startPos_));

		// 100以上離れたらフラグを折る
		if (dist_ >= P_SHOT_MOVE_LIMIT)
		{
			isAlive_ = false;

		}
		// モデルセット
		MV1SetPosition(modelId_, pos_);
	}

}

void PlayerShot::ReLoad(void)
{
	// 弾切れ
	if (!isAlive_
		&& InputManager::GetInstance()->IsTrgDown(MOUSE_INPUT_LEFT)
		&& ammo_ == 0) {
		// 弾切れ音再生
		SoundManager::GetInstance()->PlayNoAmmo();
	}

	// リロード
	// マガジン取得状態でRを押したら
	if (InputManager::GetInstance()->IsTrgDown(KEY_INPUT_R) && magazine_ >= 1 && ammo_ < 21)
	{
		// マガジン数を減らす
		magazine_--;
		// 弾数を最大にする
		ammo_ = MAX_AMMO;

		// リロード音再生
		SoundManager::GetInstance()->PlayReLoad();
	}
}

int PlayerShot::GetModelId() const
{
	return modelId_;
}

VECTOR PlayerShot::GetPos()
{
	return pos_;
}

VECTOR PlayerShot::GetDir()
{
	return dir_;
}

bool PlayerShot::GetAlive(void)
{
	return isAlive_;
}

void PlayerShot::SetAlive(bool isAlive)
{
	isAlive_ = isAlive;
}

// マガジン取得
void PlayerShot::SetMagazine(int magazine)
{
	magazine_ += magazine;
}
