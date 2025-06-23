#include "ItemKit.h"

ItemKit::ItemKit(void)
{
}

ItemKit::~ItemKit(void)
{
}

void ItemKit::Draw()
{
    // ワクチンが拾われてなかったら描画
    if (state_ != STATE::PICKUP_K) MV1DrawModel(modelId_);

    for (const auto& point : kitSpawnPoints)
   {
        DrawSphere3D(point.pos, 230, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), false);
   }

	// キット画像を描画
    DrawRotaGraph(500, 1020, 0.4, 0.0f, kitImg_, true);
}

void ItemKit::SetParam()
{
	scale_ = DEFAULT_KIT_SCALE;

    // キット画像
	kitImg_ = LoadGraph("Data/Image/Kit.png");
}