#include <DxLib.h>
#include "../../Manager/SoundManager.h"
#include "../../Manager/ItemManager.h"
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

    isActive_ = false;

    isPickUpV_ = false;

    pickUpTime_ = 0;

    vNumber_ = ItemManager::VACCINE_NUM;

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
    // ワクチンが拾われたら描画
    if(!isPickUpV_) MV1DrawModel(modelId_);

    // 最初のワクチン取得時に
    if( !isPickUpV_ && vNumber_ == 2 ) {

        int now = GetNowCount();
        if (now - pickUpTime_ <= SHOW_DURATION)
        {
            // 拾ってから3秒以内なら画像表示
            DrawRotaGraph(955, 540, 0.5, 0, vImage_, true);
        }
    }

    if (!isPickUpV_)
    {
        DrawFormatString(0, 50, 0xffffff, "ワクチンを回収");
    }
    else
    {
        DrawFormatString(0, 50, 0xffffff, "ドアから脱出");
    }

    DrawFormatString(0, 80, 0xffffff, "ワクチン残り個数:%d", vNumber_);

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

void ItemBase::TakePickUp(int number)
{
    // ワクチンの残り個数計算 (減らしていく)
    vNumber_ = ItemManager::VACCINE_NUM - number;

    PickUp();
}

void ItemBase::PickUp()
{
    // 残りワクチン個数が０になったら
    if (vNumber_ == 0)
    {
        isPickUpV_ = true;
        pickUpTime_ = GetNowCount();
    }

    // 取得音再生
    SoundManager::GetInstance()->PlayPickUp();
}

bool ItemBase::GetPickUp()
{
    return isPickUpV_;
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
