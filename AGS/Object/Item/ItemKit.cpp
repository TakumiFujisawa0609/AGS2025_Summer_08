#include "ItemKit.h"

ItemKit::ItemKit(void)
{
}

ItemKit::~ItemKit(void)
{
}

void ItemKit::Draw()
{
    // ƒƒNƒ`ƒ“‚ªE‚í‚ê‚Ä‚È‚©‚Á‚½‚ç•`‰æ
    if (state_ != STATE::PICKUP_K) MV1DrawModel(modelId_);

    for (const auto& point : kitSpawnPoints)
   {
        DrawSphere3D(point.pos, 230, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), false);
   }
}

void ItemKit::SetParam()
{
	scale_ = DEFAULT_KIT_SCALE;
}