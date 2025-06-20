#include <DxLib.h>
#include "ItemBullet.h"

ItemBullet::ItemBullet(void)
{
}

ItemBullet::~ItemBullet(void)
{
}

void ItemBullet::Draw()
{
	MV1DrawModel(modelId_);

	// スポーン位置の球体を描画
	for (const auto& point : bulletSpawnPoints)
	{
		DrawSphere3D(point.pos, 230, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), false);
	}
}

bool ItemBullet::isVaccineAlive()
{
	return false;
}

VECTOR ItemBullet::GetVPos()
{
	return VECTOR();
}

void ItemBullet::SetParam()
{
	scale_ = DEFAULT_BULLET_SCALE;
	angle_ = DEFAULT_BULLET_ANGLE;
}

void ItemBullet::SetApplyEffect()
{
	
}
