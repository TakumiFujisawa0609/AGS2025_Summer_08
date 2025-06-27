#include <DxLib.h>
#include "ShotManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"

PlayerShotManager::PlayerShotManager()
{
}

PlayerShotManager::~PlayerShotManager()
{
}

void PlayerShotManager::Init(Camera* camera)
{
    camera_ = camera;

    shots_.resize(MAX_SHOTS);

    for (auto& shot : shots_)
    {
        shot.Init(camera_);
        shot.SetAlive(false);
    }

    shotIntervalTimer_ = 0;
}

void PlayerShotManager::Update()
{
    if (shotIntervalTimer_ > 0)
    {
        --shotIntervalTimer_;
    }

    // ”­ŽË”»’è
    if (shotIntervalTimer_ == 0 && InputManager::GetInstance()->IsTrgDown(MOUSE_INPUT_LEFT))
    {
        Shot();
        shotIntervalTimer_ = SHOT_INTERVAL_FRAMES;
    }

    // ‚·‚×‚Ä‚Ì’e‚ðXV
    for (auto& shot : shots_)
    {
        if (shot.GetAlive())
        {
            shot.Update();
        }
    }
}

void PlayerShotManager::Draw()
{
    for (auto& shot : shots_)
    {
        if (shot.GetAlive())
        {
            shot.Draw();
        }
    }
}

void PlayerShotManager::Release()
{
    for (auto& shot : shots_)
    {
        shot.Release();
    }
}

void PlayerShotManager::Shot()
{
    // ’e‚ª‚ ‚ê‚Î”­ŽË‰Â”\i‚±‚±‚Å‚Í’e”ŠÇ—‚ðPlayerShot‘¤‚É”C‚¹‚Ä‚¢‚é‚Ì‚Å”­ŽË‰Â”\‚È‚à‚Ì‚ð’T‚·j
    for (auto& shot : shots_)
    {
        if (!shot.GetAlive())
        {
            shot.Shot();
            SoundManager::GetInstance()->PlayShot();
        }
    }
}

void PlayerShotManager::Reload()
{
    for (auto& shot : shots_)
    {
        shot.ReLoad();
    }
}