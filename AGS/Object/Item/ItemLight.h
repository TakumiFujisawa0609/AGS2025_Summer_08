#pragma once
#include "ItemBase.h"

class ItemLight : public ItemBase
{
public:
	// コンストラクタ・デストラクタ
	ItemLight(void);
	~ItemLight(void);

	void Update() override;
	void Draw() override;

	VECTOR GetLPos();

protected:

	// パラメータ設定
	void SetParam() override;

	int lightHandle_;
};

