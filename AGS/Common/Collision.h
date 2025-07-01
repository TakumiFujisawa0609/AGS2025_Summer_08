#pragma once
#include <unordered_map>
#include <DxLib.h>
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Item/ItemBase.h"
class Player;
class StageBase;
class EnemyManager;
class Camera;
class Blood;
class PlayerShot;
class AnimControl;
class ItemManager;

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
    void Init(Player* player,StageBase* stage, EnemyManager* enemy, Blood* blood, PlayerShot* pShot, Camera* camera, ItemManager* item);
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

    // プレイヤー弾とステージの当たり判定
    void CollisionPShotAndS();

    // プレイヤーとステージの当たり判定処理
    void CollisionPAndS();

	// 敵とステージの当たり判定処理
    void CollisionEAndS();

    // プレイヤーとワクチンの当たり判定
    void CollisionPAndItem();


    // プレイヤーとドアの当たり判定
    void CollisionPAndD();

    bool GetClear();

private:

    Player* player_;

	StageBase* stage_;

    EnemyManager* enemy_;

    Camera* camera_;

    Blood* blood_;

    PlayerShot* pShot_;

    AnimControl* animControl_;

    ItemManager* item_;

    // 照準と敵の当たり判定
    //MV1_COLL_RESULT_POLY hitPoly_PShot_E;
    // // 照準と敵の当たり判定
    MV1_COLL_RESULT_POLY hitPoly_PShot_E;
    // プレイヤー弾とステージの当たり判定
    MV1_COLL_RESULT_POLY_DIM hitPoly_PShot_S;

    // 敵とプレイヤーのの当たり判定
    MV1_COLL_RESULT_POLY_DIM hitPoly_E_P;
    // プレイヤーとステージの当たり判定
    MV1_COLL_RESULT_POLY hitPoly_P_S;
    // 敵とステージの当たり判定
	MV1_COLL_RESULT_POLY hitPoly_E_S;

    // 拾うキー画像
    int fKeyImg_;
    // 拾うフラグ
    int isPickKey_ = false;
    // 開くフラグ
    bool isOpenKey_ = false;

    bool isGameClear_;



    // デバッグ用
    VECTOR enemyPosS_, enemyPosE_;

    // 敵とステージの当たり判定がヒットしたかどうか
	bool isHit_E_P_ = false; 

    // プレイヤーとステージの当たり判定
    bool isHit_P_S_ = false;

    bool isHitP_V_ = false;

    // 攻撃判定
    std::unordered_map<EnemyBase*, bool> enemyAttackHit_;

    // 取得判定
    std::unordered_map<ItemBase*, bool> itemHit_;

    // プレイヤーの中心座標
    VECTOR pCenterPos_;

    VECTOR a;
    VECTOR b;
};
