#include "ItemKit.h"

ItemKit::ItemKit(void)
{
}

ItemKit::~ItemKit(void)
{
}

void ItemKit::Draw()
{
    /*for (const auto& point : kitSpawnPoints)
   {
       DrawSphere3D(point.pos, 20.0f, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), false);
   }*/
}

void ItemKit::SetParam()
{

	scale_ = DEFAULT_KIT_SCALE;
}

void ItemKit::SetApplyEffect()
{
}
