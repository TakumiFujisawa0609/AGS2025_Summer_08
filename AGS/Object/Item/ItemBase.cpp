#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/ItemManager.h"
#include "../Player.h"
#include "ItemBase.h"

ItemBase::ItemBase()
{
}

ItemBase::~ItemBase()
{
}

void ItemBase::Init(TYPE type, int baseModelId, Player* player, Camera* camera)
{
    player_ = player;

    camera_ = camera;

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
}

void ItemBase::Update()
{
    // モデルを座標にセット
    MV1SetPosition(modelId_, pos_);
}

void ItemBase::Release()
{
    MV1DeleteModel(modelId_);

	DeleteGraph(kitImg_);
    DeleteGraph(keyImg_);
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

void ItemBase::SetAngle(const VECTOR& angle)
{
    angle_ = angle;
    MV1SetRotationXYZ(modelId_, angle_);
}

VECTOR ItemBase::GetPos() const
{
    return pos_;
}

void ItemBase::SetPos(VECTOR pos)
{
    pos_ = pos;
}

bool ItemBase::IsActive() const
{
    return isActive_;
}

void ItemBase::SetActive(bool flag)
{
    isActive_ = flag;
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

bool ItemBase::IsPickedFromPosition(const VECTOR& target, float radius) const
{
    return VSize(VSub(pos_, target)) <= radius;
}

void ItemBase::SetParam()
{
}
