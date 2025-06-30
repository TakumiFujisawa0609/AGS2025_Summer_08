#pragma once
#include <vector>
#include "../Object/PlayerShot.h"
#include "../Object/Camera.h"

class PlayerShotManager
{
public:
    static constexpr int MAX_SHOTS = 20;  // 管理する最大弾数

    PlayerShotManager();
    ~PlayerShotManager();

    void Init(Camera* camera);
    void Update();
    void Draw();
    void Release();

    // 発射要求
    void Shot();

    // リロード
    void Reload();

private:
    Camera* camera_;
    std::vector<PlayerShot> shots_;

    // 弾の数
    int ammo_;

    // 発射間隔制御用タイマー
    int shotIntervalTimer_;
    static constexpr int SHOT_INTERVAL_FRAMES = 5;  // フレーム数で発射間隔
};

