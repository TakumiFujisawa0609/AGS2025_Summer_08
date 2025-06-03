#pragma once
#include "ItemBase.h"

class ItemBullet : public ItemBase
{
public:
	// コンストラクタ・デストラクタ
	ItemBullet(void);
	~ItemBullet(void);

protected:

	// パラメータ設定
	void SetParam() override;
	// 効果設定
	void SetApplyEffect() override;
};