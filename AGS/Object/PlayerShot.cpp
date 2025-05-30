#include <DxLib.h>
#include "../Object/Camera.h"
#include "../Manager/InputManager.h"
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

	//if (modelId_ == -1) {
	//	MessageBoxA(NULL, "弾モデルの読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR);
	//}

	pos_ = DEFAULT_POS;
	startPos_ = DEFAULT_POS;
	dir_ = { 0,0,0 };
	scale_ = DEFAULT_SCALE;

	isAlive_ = false;


	MV1SetScale(modelId_, scale_);
}

void PlayerShot::Update(void)
{
	if (!isAlive_ && GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		// カメラ位置と方向取得
		startPos_ = pos_ = camera_->GetPos();
		// 正規化して向きを取得（符号反転して前に飛ばす）
		dir_ = VScale(VNorm(camera_->GetForward()), -1.0f);
		isAlive_ = true;
	}

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

		MV1SetPosition(modelId_, pos_);

	}

}

void PlayerShot::Draw(void)
{
	//if(isAlive_) MV1DrawModel(modelId_);

	//if(isAlive_) DrawSphere3D(pos_, 10, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
	DrawFormatString(0, 540, 0xffffff, "isAlive:%d", isAlive_ );
	DrawFormatString(0, 500, 0xffffff, "ShotPos:(%f,%f,%f)", pos_.x, pos_.y, pos_.z);
	DrawFormatString(0, 520, 0xffffff, "dir_: (%.2f, %.2f, %.2f)", dir_.x, dir_.y, dir_.z);
	DrawFormatString(0, 560, 0xffffff, "Dist:%f", dist_);
}

void PlayerShot::Release(void)
{
	MV1DeleteModel(modelId_);
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
