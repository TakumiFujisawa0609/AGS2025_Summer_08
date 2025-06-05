#pragma once
#include "ItemBase.h"

class ItemVaccine : public ItemBase
{
public:
	// コンストラクタ・デストラクタ
	ItemVaccine(void);
	~ItemVaccine(void);

protected:

	// パラメータ設定
	void SetParam() override;
	// 効果設定
	void SetApplyEffect() override;
};