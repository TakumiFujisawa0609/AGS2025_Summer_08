#include <DxLib.h>
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
    modelId_ = MV1DeleteModel(baseModelId);

    // 初期化（座標・サイズ・角度）
    pos_ = DEFAULT_POS;
    scale_ = DEFAULT_SCALE;
    angle_ = DEFAULT_ANGLE;

    isActive_ = false;
    isPickUp_ = false;

    // 座標設定
    MV1SetPosition(modelId_, pos_);

    SetApplyEffect();
}

void ItemBase::Update()
{
}

void ItemBase::Draw()
{
}

void ItemBase::Release()
{
}

void ItemBase::SetApplyEffect()
{
}

void ItemBase::SetPickUp(bool isPickUp)
{
    isPickUp_ = isPickUp;
}

VECTOR ItemBase::GetPos() const
{
    return pos_;
}

void ItemBase::SetPos(VECTOR pos)
{
    pos_ = pos;
}

