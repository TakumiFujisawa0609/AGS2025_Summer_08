#pragma once
#include "ItemBase.h"

class ItemKit : public ItemBase
{
public:
	// コンストラクタ・デストラクタ
	ItemKit(void);
	~ItemKit(void);

	void Draw() override;

protected:

	// パラメータ設定
	void SetParam() override;
};
