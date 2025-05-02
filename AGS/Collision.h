#pragma once
class Player;
class Enemy;
class Blast;
class PlayerShot;

class Collision
{
public:

    // プレイヤーの当たり判定の球体の半径
    static constexpr float INIT_PLAYER_SPHERE_RADIUS = 80.0f;
    // 敵の当たり判定の球体の半径
    static constexpr float INIT_ENEMY_SPHERE_RADIUS = 40.0f;
    // プレイヤー弾の当たり判定の球体の半径
    static constexpr float INIT_P_SHOT_SPHERE_RADIUS = 60.0f;



    // 初期化
    void Init(Player* player, Enemy* enemy, Blast* blast, PlayerShot* pShot);
    // 更新
    void Update(void);
    // 描画
    void Draw(void);
    // 解放
    void Release(void);

    // プレイヤーと敵の当たり判定処理
    void CollisionPAndE(void);

    // プレイヤー弾と敵の当たり判定処理
    void CollisionPShotAndE(void);

private:

    Player* player_;

    Enemy* enemy_;

    Blast* blast_;

    PlayerShot* pShot_;

    // プレイヤーの当たり判定の球体の半径
    float playerSphereRadius_;
    // 敵の当たり判定の球体の半径
    float enemySphereRadius_;
    // プレイヤーと敵の当たり判定用球体の半径の合計
    float radiusPAndESum_;
    // プレイヤー弾と敵の当たり判定用球体の半径の合計
    float radiusPShotAndESum_;

    // プレイヤーと敵の当たり判定用球体の中心間の距離
    float centerDistancePandE_;
    // プレイヤー弾と敵の当たり判定用球体の中心間の距離
    float centerDistancePShotAndE_;
    float centerDistanceAbnormalPShotAndE1_;
    float centerDistanceAbnoemalPShotAndE2_;

};
