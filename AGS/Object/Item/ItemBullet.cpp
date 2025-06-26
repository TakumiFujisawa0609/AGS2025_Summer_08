#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
#include "ItemBullet.h"

ItemBullet::ItemBullet(void)
{
}

ItemBullet::~ItemBullet(void)
{
}

void ItemBullet::Draw()
{
	if (state_ != STATE::PICKUP_B) MV1DrawModel(modelId_);

	// スポーン位置の球体を描画
	for (const auto& point : bulletSpawnPoints)
	{
		DrawSphere3D(point.pos, 230, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), false);
	}
}

VECTOR ItemBullet::GetVPos()
{
	return VECTOR();
}

void ItemBullet::SetParam()
{
	scale_ = DEFAULT_BULLET_SCALE;

	// 向き設定
	MV1SetRotationXYZ(modelId_, { 0,  AsoUtility::Deg2RadF(-90.0f), 0 });
}