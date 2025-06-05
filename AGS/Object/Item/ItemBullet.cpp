#include <DxLib.h>
#include "ItemBullet.h"

ItemBullet::ItemBullet(void)
{
}

ItemBullet::~ItemBullet(void)
{
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
