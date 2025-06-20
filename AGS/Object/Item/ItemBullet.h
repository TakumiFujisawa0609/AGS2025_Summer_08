#pragma once
#include "ItemBase.h"

class ItemBullet : public ItemBase
{
public:
	// コンストラクタ・デストラクタ
	ItemBullet(void);
	~ItemBullet(void);

	void Draw() override;

	bool isVaccineAlive();
	VECTOR GetVPos();

protected:

	// パラメータ設定
	void SetParam() override;
	// 効果設定
	void SetApplyEffect() override;

	bool isVaccineAlive_;
};