#pragma once
#include "EnemyBase.h"
class EnemyFemale : public EnemyBase
{
public:

	static constexpr SpawnPoint femaleWave2SpawnPoints[2] = {
	{4670, 0, -483},
	{2467, 0, -659}
	};

	// コンストラクタ・デストラクタ
	EnemyFemale(void);
	~EnemyFemale(void);

	void ChangeStateDist() override;
	void ChangeRun(void) override;
	void ChangeDie();

protected:

	bool hasFPlayedRunSound_ = false; // 走り声再生したか

	// パラメータ設定
	void SetParam() override;
};

