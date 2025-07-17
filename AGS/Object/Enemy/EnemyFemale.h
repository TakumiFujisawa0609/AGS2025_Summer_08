#pragma once
#include "EnemyBase.h"
class EnemyFemale : public EnemyBase
{
public:

	static constexpr SpawnPoint femaleWave2SpawnPoints[4] = {
	{4670, 0, -483},
	{2467, 0, -659},
	{-370.0f, 0, 450.0f},
	{-370.0f, 0, -327.0f}
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

