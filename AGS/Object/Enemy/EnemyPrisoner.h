#pragma once
#include "EnemyBase.h"
class EnemyPrisoner : public EnemyBase
{
public:

	static constexpr SpawnPoint prisonerWave1SpawnPoints[2] = {
	{4670, 0, -483},
	{6761, 0, -1254}
	};

	// コンストラクタ・デストラクタ
	EnemyPrisoner(void);
	~EnemyPrisoner(void);

	void ChangeStateDist() override;
	void ChangeRun(void) override;

protected:

	// パラメータ設定
	void SetParam() override;
};

