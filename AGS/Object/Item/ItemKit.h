#pragma once
#include "ItemBase.h"

class ItemKit : public ItemBase
{
public:
	// コンストラクタ・デストラクタ
	ItemKit(void);
	~ItemKit(void);

protected:

	// パラメータ設定
	void SetParam() override;
	// 効果設定
	void SetApplyEffect() override;
};
