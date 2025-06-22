#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
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

	// 待機状態にする
	ChangeState(STATE::STANBY);

    // パラメータ設定
    SetParam();

    // 大きさ設定
    MV1SetScale(modelId_, scale_);

    // モデルを座標にセット
    MV1SetPosition(modelId_, pos_);

	// 向き設定
    MV1SetRotationXYZ(modelId_, { 0,  AsoUtility::Deg2RadF(90.0f), AsoUtility::Deg2RadF(90.0f) });

    // 少し明るくする
    MV1SetMaterialEmiColor(modelId_, -1, GetColorF(0.5f, 0.5f, 0.5f, 1.0f)); // アイテム
}

void ItemBase::Update()
{
    // モデルを座標にセット
    MV1SetPosition(modelId_, pos_);
}

void ItemBase::Release()
{
    MV1DeleteModel(modelId_);
}

// 状態遷移
void ItemBase::ChangeState(STATE state)
{
	state_ = state;

    switch (state_)
    {
    case STATE::STANBY:

	case STATE::PICKUP_V:

    case STATE::PICKUP_B:

    case STATE::PICKUP_K:
		break;
    }
}

void ItemBase::PickUp()
{
}

VECTOR ItemBase::GetPos() const
{
    return pos_;
}

void ItemBase::SetPos(VECTOR pos)
{
    pos_ = pos;
}

// アイテムの種別を取得
ItemBase::TYPE ItemBase::GetType() const
{
    return type_;
}

// 衝突判定が有効な状態
bool ItemBase::IsCollisionState(void)
{
    return state_ == STATE::STANBY;
}

void ItemBase::SetParam()
{
}
