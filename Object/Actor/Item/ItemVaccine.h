#pragma once
#include "ItemBase.h"

class ItemVaccine : public ItemBase
{
public:
	// コンストラクタ・デストラクタ
	ItemVaccine(void);
	~ItemVaccine(void);

	void Draw() override;

protected:

	// パラメータ設定
	void SetParam() override;
};