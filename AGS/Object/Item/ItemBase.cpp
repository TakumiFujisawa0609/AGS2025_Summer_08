#include <DxLib.h>
#include "../../Manager/SoundManager.h"
#include "ItemBase.h"

ItemBase::ItemBase()
{
}

ItemBase::~ItemBase()
{
}

void ItemBase::Init(TYPE type, int baseModelId)
{
    // 種別
    type_ = type;

    // モデルロード
    modelId_ = MV1DuplicateModel(baseModelId);

    vImage_ = LoadGraph("Data/Image/GetVaccine.png");

    isActive_ = false;
    isPickUp_ = false;

    pickUpTime_ = 0;

    // パラメータ設定
    SetParam();

    // 大きさ設定
    MV1SetScale(modelId_, scale_);
    

    // 効果設定
    SetApplyEffect();
}

void ItemBase::Update()
{
    // 位置をモデルに反映
    MV1SetPosition(modelId_, pos_);

}

void ItemBase::Draw()
{
    if(!isPickUp_) MV1DrawModel(modelId_);
    else {

        int now = GetNowCount();
        if (now - pickUpTime_ <= SHOW_DURATION)
        {
            // 拾ってから3秒以内なら画像表示
            DrawRotaGraph(955, 540, 0.5, 0, vImage_, true);
        }
    }

    if (!isPickUp_)
    {
        DrawFormatString(0, 50, 0xffffff, "ワクチンを回収");
    }
    else
    {
        DrawFormatString(0, 50, 0xffffff, "ドアから脱出");
    }


    // スポーン位置の球体を描画
    /*for (const auto& point : bulletSpawnPoints)
    {
        DrawSphere3D(point.pos, 20.0f, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), false);
    }*/

    /*for (const auto& point : kitSpawnPoints)
    {
        DrawSphere3D(point.pos, 20.0f, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), false);
    }*/

    //for (auto point : vaccineSpawnPoints)
    //{
    //    point.pos = VAdd(point.pos, { 0, 50, -0 });

    //    DrawSphere3D(point.pos, 230, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
    //}
}

void ItemBase::Release()
{
    MV1DeleteModel(modelId_);

    DeleteGraph(vImage_);
}

void ItemBase::SetApplyEffect()
{
}

void ItemBase::SetPickUp(bool isPickUp)
{
    isPickUp_ = isPickUp;
}

void ItemBase::SetPickUp()
{
    if (!isPickUp_)
    {
        isPickUp_ = true;
        pickUpTime_ = GetNowCount();

        SoundManager::GetInstance()->PlayPickUp();
    }
}

bool ItemBase::GetPickUp()
{
    return isPickUp_;
}

VECTOR ItemBase::GetPos() const
{
    return pos_;
}

void ItemBase::SetPos(VECTOR pos)
{
    pos_ = pos;
}

void ItemBase::SetParam()
{
}
