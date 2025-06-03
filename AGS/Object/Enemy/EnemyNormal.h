#pragma once
#include "EnemyBase.h"
class EnemyNormal : public EnemyBase
{
public:
	// コンストラクタ・デストラクタ
	EnemyNormal(void);
	~EnemyNormal(void);

protected:

	// パラメータ設定
	void SetParam() override;
};
