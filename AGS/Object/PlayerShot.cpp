#include <DxLib.h>
#include "../Manager/Application.h"
#include "../Object/Camera.h"
#include "../Object/Player.h"
#include "../Manager/SoundManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "PlayerShot.h"

PlayerShot::PlayerShot() {}
PlayerShot::~PlayerShot() {}

void PlayerShot::Init(Camera* camera, Player* player)
{
	camera_ = camera;
	player_ = player;

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

	// 撃つ・リロード
	Shot();
	ReLoad();

	// 弾の配列を回す
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
		//	DrawSphere3D(shot.pos, 10, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
		}
	}

	DrawRotaGraph(1770, 950, 0.23f, 0.0f, gunCircleImg_, true);
	DrawRotaGraph(1770, 928, 0.35f, 0.0f, image_, true);

	int x = 1770;
	int y = 990;
	int ammoOffsetX = (ammo_ < 10) ? 16 : 0;
	int maxOffsetX = (maxMagazine_ < 10) ? 3 : 0;

	SetFontSize(42);
	DrawFormatString(x - 50 + ammoOffsetX, y - 2, 0x00ff00, "%d", ammo_);
	SetFontSize(23);
	DrawString(x + 0, y + 12, "/", 0xd3d3d3);
	SetFontSize(26);
	DrawFormatString(x + 17 + maxOffsetX, y + 12, 0xd3d3d3, "%d", maxMagazine_);
}

void PlayerShot::Release(void)
{
	DeleteGraph(gunCircleImg_);
	DeleteGraph(rKeyImg_);
	MV1DeleteModel(modelId_);
}

void PlayerShot::Shot(void)
{
	// リロード中なら撃てない
	if (isReloading_ || !player_->GetAlive()) return;

	if (shotTimer_ > 0) return;
	if (!InputManager::GetInstance().IsTrgMouseLeft()) return;
	if (ammo_ <= 0) return;

	for (auto& shot : shots_)
	{
		if (!shot.isAlive)
		{
			VECTOR forward = VNorm(camera_->GetForward());
			VECTOR offset = VScale(forward, -40.0f); // 後ろ方向へずらす
			VECTOR startPos = VAdd(camera_->GetPos(), offset);

			shot.pos = shot.startPos = startPos;
			shot.dir = VScale(forward, -1.0f);
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
	float deltaTime = SceneManager::GetInstance()->GetDeltaTime();

	// 弾切れ時に左クリックで空撃ち音
	if (InputManager::GetInstance().IsTrgMouseLeft() && ammo_ == 0 
		&& !isReloading_ && player_->GetAlive())
	{
		SoundManager::GetInstance()->PlayNoAmmo();
		isReload_ = (maxMagazine_ > 0);
	}

	// Rキーを押した瞬間にリロード開始
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_R) && ammo_ < MAX_AMMO 
		&& maxMagazine_ > 0 && !isReloading_ && player_->GetAlive())
	{
		isReloading_ = true;
		reloadTimer_ = 0.0f;

		SoundManager::GetInstance()->PlayReLoad();
	}

	// リロード中処理
	if (isReloading_)
	{
		reloadTimer_ += deltaTime;

		isReload_ = false;

		// 3秒経過したらリロード完了
		if (reloadTimer_ >= 1.8f)
		{
			int needAmmo = MAX_AMMO - ammo_;
			int reloadAmmo = (needAmmo < maxMagazine_) ? needAmmo : maxMagazine_;

			ammo_ += reloadAmmo;
			maxMagazine_ -= reloadAmmo;

			isReloading_ = false;
		}
	}
}

void PlayerShot::KeyDraw(void)
{
	if (isReload_ && player_->GetAlive())
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2 - 18, Application::SCREEN_SIZE_Y / 2 + 46, 0.23f, 0.0f, rKeyImg_, true);
		SetFontSize(23);
		DrawFormatString(Application::SCREEN_SIZE_X / 2 - 3, Application::SCREEN_SIZE_Y / 2 + 34, 0xffffff, "リロード");
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
