#pragma once


class ItemBase {
public:

    enum class TYPE
    {
        BULLET,
        HEAL,
        VACCINE,
        MAX
    };

    // スポーン位置
    struct SpawnPoint
    {
        VECTOR pos;
    };

    static constexpr SpawnPoint spawnPoints[2] = {
        {100.0f, 0.0f, 100.0f},
        {700.0f, 0.0f, 1400.0f}
    };

    // 初期座標・サイズ
    static constexpr VECTOR DEFAULT_POS = { 0,0,0 };
    static constexpr VECTOR DEFAULT_SCALE = { 0,0,0 };

    // 初期角度
    static constexpr VECTOR DEFAULT_ANGLE = { 0.0f, 0.0f, 0.0f };

    ItemBase();
    virtual ~ItemBase();

    void Init(TYPE type, int baseModel);        // 初期化
    void Update();      // 更新
    void Draw();        // 描画
    void Release();     // 解放

    void SetPickUp(bool isPickUp);   // 取得したかどうか

    VECTOR GetPos() const; // 座標取得
    void SetPos(VECTOR pos);  //座標設定

protected:

    // 種別
    TYPE type_;

    int modelId_;    // モデルID
    VECTOR pos_;     // アイテムの位置
    VECTOR scale_;   // サイズ
    VECTOR angle_;   // 角度

    bool isPickUp_;
    bool isActive_;    // 使用判定

    virtual void SetParam() = 0;    // パラメータ設定
    virtual void SetApplyEffect() = 0;  // 効果適用
};
