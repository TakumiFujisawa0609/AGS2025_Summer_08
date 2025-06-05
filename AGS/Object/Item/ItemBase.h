#pragma once
#include <DxLib.h>

class ItemBase {
public:

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

    static constexpr SpawnPoint bulletSpawnPoints[2] = {
        {100.0f, 0.0f, 100.0f},
        {700.0f, 0.0f, 1400.0f}
    };

    static constexpr SpawnPoint kitSpawnPoints[2] = {
       {100.0f, 0.0f, 100.0f},
       {700.0f, 0.0f, 1400.0f}
    };

    static constexpr SpawnPoint vaccineSpawnPoints[1] = {
       {0.0f, 0.0f, 7750.0f}
       //{100.0f, 0.0f, 100.0f}
       //{700.0f, 0.0f, 1400.0f}
    };


    // 初期サイズ
    static constexpr VECTOR DEFAULT_BULLET_SCALE = { 1,1,1 };

    // 初期サイズ
    static constexpr VECTOR DEFAULT_KIT_SCALE = { 0.2,0.2,0.2 };

    // 初期サイズ
    static constexpr VECTOR DEFAULT_VACCINE_SCALE = { 0.1,0.1,0.1 };

    // 初期角度
    static constexpr VECTOR DEFAULT_BULLET_ANGLE = { 0.0f, 0.0f, 0.0f };
    static constexpr VECTOR DEFAULT_KIT_ANGLE = { 0.0f, 0.0f, 0.0f };
    static constexpr VECTOR DEFAULT_VACCINE_ANGLE = { 0.0f, 0.0f, 0.0f };

    static constexpr int SHOW_DURATION = 2500;
    ItemBase();
    virtual ~ItemBase();

    void Init(TYPE type, int baseModel);        // 初期化
    void Update();      // 更新
    void Draw();        // 描画
    void Release();     // 解放

    void SetPickUp(bool isPickUp);   // 取得したかどうか
    void SetPickUp();
    bool GetPickUp();

    VECTOR GetPos() const; // 座標取得
    void SetPos(VECTOR pos);  //座標設定

protected:

    // 種別
    TYPE type_;

    int modelId_;    // モデルID
    int vImage_;
    VECTOR pos_;     // アイテムの位置
    VECTOR scale_;   // サイズ
    VECTOR angle_;   // 角度

    bool isPickUp_;
    bool isActive_;    // 使用判定

    bool isVaccineAlive_;

    int pickUpTime_;   // 拾った時間（ミリ秒）

    virtual void SetParam() = 0;    // パラメータ設定
    virtual void SetApplyEffect() = 0;  // 効果適用
};
