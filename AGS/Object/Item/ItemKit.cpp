#include "../../utility/AsoUtility.h"
#include "../Player.h"
#include "ItemKit.h"

ItemKit::ItemKit(void)
{
}

ItemKit::~ItemKit(void)
{
}

void ItemKit::Draw()
{
    VECTOR pPos = player_->GetPPos();
    float dis = VSize(VSub(pPos, pos_));

    // キットが拾われてなかったら描画
    if (dis < 2400 && state_ != STATE::PICKUP_K)
    {
        MV1DrawModel(modelId_);
    }

    for (const auto& point : kitSpawnPoints)
    {
        DrawSphere3D(point.pos, 230, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), false);
    }

	// キット画像を描画
    DrawRotaGraph(1570, 1013, 0.1, 0.0f, kitImg_, true);
    // キーアイコンを描画
    DrawRotaGraph(330, 1020, 0.1, 0.0f, keyImg_, true);
}

void ItemKit::SetParam()
{
	scale_ = DEFAULT_KIT_SCALE;

    // キット画像
	kitImg_ = LoadGraph("Data/Image/Kit.png");
    // キーアイコン画像
    keyImg_ = LoadGraph("Data/Image/Q_Key.png");

    // 向き設定
    MV1SetRotationXYZ(modelId_, { 0,  AsoUtility::Deg2RadF(90.0f), AsoUtility::Deg2RadF(90.0f) });
}