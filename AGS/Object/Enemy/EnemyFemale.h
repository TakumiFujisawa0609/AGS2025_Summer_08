#pragma once
#include "EnemyBase.h"
class EnemyFemale : public EnemyBase
{
public:

	static constexpr SpawnPoint femaleWave1SpawnPoints[2] = {
	{2467, 0, -659},
	{2267, 0, -659}
	};

	// コンストラクタ・デストラクタ
	EnemyFemale(void);
	~EnemyFemale(void);

	void ChangeStateDist() override;
	void ChangeRun(void) override;

protected:

	// パラメータ設定
	void SetParam() override;
};

