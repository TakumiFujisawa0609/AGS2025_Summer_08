#pragma once
#include "EnemyBase.h"
class EnemyPrisoner : public EnemyBase
{
public:

	static constexpr SpawnPoint prisonerWave1SpawnPoints[4] = {
	{4670, 0, -483},
	{6761, 0, -1254},
	{ 8786, 0, 677 },
	{ 8986, 0, 677 }
	};

	static constexpr SpawnPoint prisonerWave2SpawnPoints[2] = {
		{-1170.0f, 0, 450.0f},
		{-1170.0f, 0, -327.0f}
	};

	// コンストラクタ・デストラクタ
	EnemyPrisoner(void);
	~EnemyPrisoner(void);

	void ChangeStateDist() override;
	void ChangeWalk(void) override;
	void ChangeDie() override;

protected:
	bool hasPPlayedRunSound_ = false; // 走り声再生したか

	// パラメータ設定
	void SetParam() override;
};

