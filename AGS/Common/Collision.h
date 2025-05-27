#pragma once
#include <DxLib.h>
class Player;
class StageBase;
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

    // レイの補正値
    static constexpr float RAY_COL_Y = 150.0f;


    // 初期化
    void Init(Player* player,StageBase* stage, EnemyBase* enemy, Blast* blast, PlayerShot* pShot);
    // 更新
    void Update(void);
    // 描画
    void Draw(void);
    // 解放
    void Release(void);

    // プレイヤーと敵の当たり判定処理
    void CollisionPAndE();

    // プレイヤー弾と敵の当たり判定処理
    void CollisionPShotAndE();

	// 敵とステージの当たり判定処理
    void CollisionEAndStage();

private:

    Player* player_;

	StageBase* stage_;

    EnemyBase* enemy_;

    Blast* blast_;

    PlayerShot* pShot_;

    // 敵とプレイヤーのの当たり判定の球体の半径
    MV1_COLL_RESULT_POLY_DIM hitPoly_E_P;
    // 敵とステージの当たり判定
	MV1_COLL_RESULT_POLY hitPoly_E_S;


#ifdef _DEBUG
    // デバッグ用
    VECTOR enemyPosS_, enemyPosE_;

    // 敵とステージの当たり判定がヒットしたかどうか
	bool isHit_E_P = false; 

    // プレイヤーの中心座標
    VECTOR pCenterPos_;

#endif // _DEBUG
};
