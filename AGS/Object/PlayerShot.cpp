#include <DxLib.h>
#include "../Manager/Application.h"
#include "../Object/Camera.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"
#include "PlayerShot.h"

PlayerShot::PlayerShot() {}
PlayerShot::~PlayerShot() {}

void PlayerShot::Init(Camera* camera)
{
	camera_ = camera;

	image_ = LoadGraph("Data/Image/gun.png");
	gunCircleImg_ = LoadGraph("Data/Image/gunCircle.png");
	rKeyImg_ = LoadGraph("Data/Image/RKey.png");

	modelId_ = MV1LoadModel("Data/Model/bullet/bullet.mv1");
	scale_ = DEFAULT_SCALE;
	MV1SetScale(modelId_, scale_);

	ammo_ = MAX_AMMO;
	maxMagazine_ = MAX_AMMO;

	shots_.resize(MAX_SHOTS);
	shotTimer_ = 0;
}

void PlayerShot::Update(void)
{
	if (shotTimer_ > 0) --shotTimer_;

	Shot();
	ReLoad();

	for (auto& shot : shots_)
	{
		if (!shot.isAlive) continue;

		shot.pos = VAdd(shot.pos, VScale(shot.dir, SHOT_SPEED));
		shot.dist = VSize(VSub(shot.pos, shot.startPos));

		if (shot.dist >= P_SHOT_MOVE_LIMIT)
		{
			shot.isAlive = false;
			continue;
		}

		MV1SetPosition(modelId_, shot.pos);
	}
}

void PlayerShot::Draw(void)
{
	for (const auto& shot : shots_)
	{
		if (shot.isAlive)
		{
	//		DrawSphere3D(shot.pos, 10, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
		}
	}

	DrawRotaGraph(120, 990, 0.16f, 0.0f, gunCircleImg_, true);
	DrawRotaGraph(120, 970, 0.23f, 0.0f, image_, true);

	int x = 130;
	int y = 990;
	int ammoOffsetX = (ammo_ < 10) ? 16 : 0;
	int maxOffsetX = (MAX_AMMO < 10) ? 12 : 0;

	SetFontSize(36);
	DrawFormatString(x - 50 + ammoOffsetX, y + 18, 0x00ff00, "%d", ammo_);
	SetFontSize(21);
	DrawString(x - 11, y + 30, "/", 0xd3d3d3);
	SetFontSize(20);
	DrawFormatString(x + 3 + maxOffsetX, y + 32, 0xd3d3d3, "%d", maxMagazine_);
}

void PlayerShot::Release(void)
{
	DeleteGraph(gunCircleImg_);
	DeleteGraph(rKeyImg_);
	MV1DeleteModel(modelId_);
}

void PlayerShot::Shot(void)
{
	if (shotTimer_ > 0) return;
	if (!InputManager::GetInstance().IsClickMouseLeft()) return;
	if (ammo_ <= 0) return;

	for (auto& shot : shots_)
	{
		if (!shot.isAlive)
		{
			shot.pos = shot.startPos = camera_->GetPos();
			shot.dir = VScale(VNorm(camera_->GetForward()), -1.0f);
			shot.dist = 0.0f;
			shot.isAlive = true;

			ammo_--;
			SoundManager::GetInstance()->PlayShot();
			shotTimer_ = SHOT_INTERVAL;
			break;
		}
	}
}

void PlayerShot::ReLoad(void)
{
	// 左クリック時、弾が0なら弾切れ音
	if (InputManager::GetInstance().IsClickMouseLeft() && ammo_ == 0)
	{
		SoundManager::GetInstance()->PlayNoAmmo();
		isReload_ = (maxMagazine_ > 0);
	}

	// Rキーでリロード
	if (InputManager::GetInstance().IsClickMouseLeft() && ammo_ < MAX_AMMO && maxMagazine_ > 0)
	{
		int needAmmo = MAX_AMMO - ammo_;
		int reloadAmmo;

		if (needAmmo < maxMagazine_) {
			reloadAmmo = needAmmo;
		}
		else {
			reloadAmmo = maxMagazine_;
		}

		ammo_ += reloadAmmo;
		maxMagazine_ -= reloadAmmo;

		isReload_ = false;

		SoundManager::GetInstance()->PlayReLoad();
	}
}

void PlayerShot::KeyDraw(void)
{
	if (isReload_)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2 - 18, Application::SCREEN_SIZE_Y / 2 + 58, 0.14f, 0.0f, rKeyImg_, true);
		DrawFormatString(Application::SCREEN_SIZE_X / 2 - 5, Application::SCREEN_SIZE_Y / 2 + 49, 0xffffff, "リロード");
	}
}

VECTOR PlayerShot::GetPos() { return camera_->GetPos(); } // 弾の位置ではなくカメラ位置
VECTOR PlayerShot::GetDir() { return VScale(VNorm(camera_->GetForward()), -1.0f); }
bool PlayerShot::GetAlive(void)
{
	for (const auto& shot : shots_)
	{
		if (shot.isAlive) return true;
	}
	return false;
}
void PlayerShot::SetAlive(bool isAlive)
{
	if (!isAlive)
	{
		for (auto& shot : shots_)
		{
			shot.isAlive = false;
		}
	}
}

std::vector<PlayerShot::ShotData>& PlayerShot::GetShots()
{
	return shots_;
}

void PlayerShot::SetMagazine()
{
	maxMagazine_ += MAX_AMMO;
}
