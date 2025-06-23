#pragma once
#include <DxLib.h>
class Player;


class ItemBase {
public:
    enum class STATE
    {
        STANBY,
		PICKUP_V,    // ワクチン取得
        PICKUP_B,    // 弾薬箱取得
		PICKUP_K,    // 医療キット取得
        MAX
    };

    enum class TYPE
    {
        BULLET,
        KIT,
        VACCINE,
        MAX
    };

    // スポーン位置
    struct SpawnPoint
    {
        VECTOR pos;
    };

    static constexpr SpawnPoint bulletSpawnPoints[1] = {
       {200.0f, 146.0f, -300.0f}
    };

    static constexpr SpawnPoint kitSpawnPoints[1] = {
       {200.0f, 146.0f, 550.0f}
    };

    static constexpr SpawnPoint vaccineSpawnPoints[3] = {
       {-800.0f, 0.0f, -500.0f},
       {-200.0f, 0.0f, -600.0f},
       {-200.0f, 0.0f, 400.0f}
    };

    // 初期サイズ
    static constexpr VECTOR DEFAULT_BULLET_SCALE = { 1,1,1 };

    // 初期サイズ
    static constexpr VECTOR DEFAULT_KIT_SCALE = { 0.15,0.15,0.15 };

    // 初期サイズ
    static constexpr VECTOR DEFAULT_VACCINE_SCALE = { 0.1,0.1,0.1 };

    // 初期角度
    static constexpr VECTOR DEFAULT_BULLET_ANGLE = { 0.0f, 0.0f, 0.0f };
    static constexpr VECTOR DEFAULT_KIT_ANGLE = { 0.0f, 0.0f, 0.0f };
    static constexpr VECTOR DEFAULT_VACCINE_ANGLE = { 0.0f, 0.0f, 0.0f };

    ItemBase();
    virtual ~ItemBase();

    void Init(TYPE type, int baseModel);        // 初期化
    void Update();      // 更新
    virtual void Draw() = 0;      // 描画
    void Release();     // 解放

    void ChangeState(STATE state);

    void PickUp();


    VECTOR GetPos() const; // 座標取得
    void SetPos(VECTOR pos);  //座標設定

    // 種別取得
    ItemBase:: TYPE GetType() const;

    // 衝突判定が有効な状態
    bool IsCollisionState(void);

protected:

    // 状態
    STATE state_;
    // 種別
    TYPE type_;

    int modelId_;    // モデルID
    VECTOR pos_;     // アイテムの位置
    VECTOR scale_;   // サイズ
    VECTOR angle_;   // 角度

    bool isActive_;    // 使用判定

    bool isVaccineAlive_;

    int kitImg_; // キットの画像ID

    virtual void SetParam() = 0;    // パラメータ設定

};
