#pragma once
#include "ItemBase.h"

class ItemBullet : public ItemBase
{
public:
	// コンストラクタ・デストラクタ
	ItemBullet(void);
	~ItemBullet(void);

	void Draw() override;

	VECTOR GetVPos();

protected:

	// パラメータ設定
	void SetParam() override;
	

	bool isVaccineAlive_;
};