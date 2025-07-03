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
        PICKUP_L,
        MAX
    };

    enum class TYPE
    {
        BULLET,
        KIT,
        VACCINE,
        LIGHT,
        MAX
    };

    // スポーン位置
    struct SpawnPoint
    {
        VECTOR pos;
    };

    static constexpr SpawnPoint bulletSpawnPoints[5] = {
       {195.0f, 125.0f, -327.0f},
        {2575.0f, 125.0f, 3796.0f },
        {4820.0f, 125.0f, -3700.0f},
        {7432.0f, 125.0f, -1430.0f},
        {7432.0f, 125.0f, 1520.0f}
    };

    static constexpr SpawnPoint kitSpawnPoints[2] = {
       {200.0f, 146.0f, 455.0f},
        {4841.0f, 146.0f, 820.0f }
    };

    static constexpr SpawnPoint vaccineSpawnPoints[3] = {
       {4815.0f, 129.0f, 1550.0f},
       {3466.0f, 129.0f, -3455.0f},
       {8830.0f, 129.0f, -12.0f}
    };

    // 初期サイズ
    static constexpr VECTOR DEFAULT_BULLET_SCALE = { 2,2,2 };

    // 初期サイズ
    static constexpr VECTOR DEFAULT_KIT_SCALE = { 0.15,0.15,0.15 };

    // 初期サイズ
    static constexpr VECTOR DEFAULT_VACCINE_SCALE = { 0.057, 0.057,0.057 };

    // 初期角度
    static constexpr VECTOR DEFAULT_BULLET_ANGLE = { 0.0f, 0.0f, 0.0f };
    static constexpr VECTOR DEFAULT_KIT_ANGLE = { 0.0f, 0.0f, 0.0f };
    static constexpr VECTOR DEFAULT_VACCINE_ANGLE = { 0.0f, 0.0f, 0.0f };

    ItemBase();
    virtual ~ItemBase();

    void Init(TYPE type, int baseModel, Player* player);        // 初期化
    virtual void Update();      // 更新
    virtual void Draw() = 0;      // 描画
    void Release();     // 解放

    void ChangeState(STATE state);

    void PickUp();


    VECTOR GetPos() const; // 座標取得
    void SetPos(VECTOR pos);  //座標設定

    bool IsActive() const;
    void SetActive(bool flag);


    // 種別取得
    ItemBase:: TYPE GetType() const;

    // 衝突判定が有効な状態
    bool IsCollisionState(void);

protected:
    Player* player_;

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
	int keyImg_; // キーアイコンの画像ID

    virtual void SetParam() = 0;    // パラメータ設定

};
