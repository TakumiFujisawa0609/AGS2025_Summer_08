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
	isPickUpAllV_ = false;

    pickUpTime_ = 0;

    vNumber_ = ItemManager::VACCINE_NUM;

	ChangeState(STATE::STANBY);

    // パラメータ設定
    SetParam();

    // 大きさ設定
    MV1SetScale(modelId_, scale_);

    // モデルを座標にセット
    MV1SetPosition(modelId_, pos_);

    // 少し明るくする
    MV1SetMaterialEmiColor(modelId_, -1, GetColorF(0.5f, 0.5f, 0.5f, 1.0f)); // アイテム
   
    // 効果設定
    SetApplyEffect();
}

void ItemBase::Update()
{
    // モデルを座標にセット
    MV1SetPosition(modelId_, pos_);
}

void ItemBase::Release()
{
    MV1DeleteModel(modelId_);

    DeleteGraph(vImage_);
}

// 状態遷移
void ItemBase::ChangeState(STATE state)
{
	state_ = state;

    switch (state_)
    {
    case STATE::STANBY:
		isPickUpV_ = false;
	case STATE::PICKUP:
		isPickUpV_ = true;
		break;
    }
}

// ワクチン取得処理
void ItemBase::TakePickUpV()
{
    // ワクチン取得状態にする
    ChangeState(STATE::PICKUP);
}

void ItemBase::PickUp()
{
}

bool ItemBase::GetPickUp()
{
    return isPickUpAllV_;
}

VECTOR ItemBase::GetPos() const
{
    return pos_;
}

void ItemBase::SetPos(VECTOR pos)
{
    pos_ = pos;
}

// 衝突判定が有効な状態
bool ItemBase::IsCollisionState(void)
{
    return state_ == STATE::STANBY;
}

void ItemBase::SetParam()
{
}
