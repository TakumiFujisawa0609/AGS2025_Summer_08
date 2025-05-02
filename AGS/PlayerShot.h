#pragma once
#include <DxLib.h>
#include "Application.h"
class Player;

class PlayerShot
{
public:

    PlayerShot();
    ~PlayerShot();

    void Init(Player* player);    // 初期化
    void Update();  // 更新
    void Draw();    // 描画
    void Release(); // 解放

    // プレイヤー弾の座標を取得
    VECTOR GetPShotPos();


    // プレイヤー弾の生存判定を設定
    void SetIsAlivePShot(bool isAlivePShot);
    // プレイヤー弾の生存判定を取得
    bool GetIsAlivePShot(void);

private:

    Player* player_; // プレイヤーのインスタンス

    // 弾のモデルID
    int pShotModelId_;
 
    // 弾の座標
    VECTOR pShotPos_;
    // 弾の生存判定
    bool isAlivePShot_;
   


};

