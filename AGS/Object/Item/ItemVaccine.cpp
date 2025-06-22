#include <DxLib.h>
#include "ItemVaccine.h"

ItemVaccine::ItemVaccine(void)
{
}

ItemVaccine::~ItemVaccine(void)
{
}

void ItemVaccine::Draw()
{
    // ワクチンが拾われてなかったら描画
    if (state_ != STATE::PICKUP_V) MV1DrawModel(modelId_);

	// スポーン位置の球体を描画
	for (const auto& point : vaccineSpawnPoints)
	{
		DrawSphere3D(point.pos, 230, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), false);
	}
}

void ItemVaccine::SetParam()
{
	scale_ = DEFAULT_VACCINE_SCALE;
}

