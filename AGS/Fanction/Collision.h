#pragma once
class Player;
class EnemyBase;
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
    void Init(Player* player, EnemyBase* enemy, Blast* blast, PlayerShot* pShot);
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

    EnemyBase* enemy_;

    Blast* blast_;

    PlayerShot* pShot_;



};
