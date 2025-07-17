#pragma once
#include "EnemyBase.h"
class EnemyNormal : public EnemyBase
{
public:

	static constexpr SpawnPoint wave1SpawnPoints[13] = {
		{2467, 0, -659},
		{3552, 0, 763},
		//{4670, 0, -483},
		{4596, 0, 2034},
		{3679, 0, 2965},
		{2857, 0, 2194},
		{4680, 0, -3500.0f},
		{2739, 0, -1770},
		{3070, 0, -3560},
		{6215, 0, 460},
		{7443, 0, 1222},
		{8786, 0, 577},
		//{6761, 0, -1254},
		{7659, 0, -986},
		{8786, 0, -623}
	};

	static constexpr SpawnPoint wave2SpawnPoints[12] = {
		//{2467, 0, -659},
		{3552, 0, 763},
		//{4670, 0, -483},
		//{4596, 0, 2034},
		{3679, 0, 2965},
		{2857, 0, 2194},
		{4680, 0, -3500.0f},
		{2739, 0, -1770},
		//5{3070, 0, -3560},
		{6215, 0, 460},
		{7443, 0, 1222},
		{9811, 0, 577},
		{6761, 0, -1254},
		{-370.0f, 0, 0.0f},
		{-370.0f, 0, 0},
		{7659, 0, -986}
		//{8786, 0, -623}
	};

	// コンストラクタ・デストラクタ
	EnemyNormal(void);
	~EnemyNormal(void);

	void ChangeWalk(void) override;
	void ChangeDie(void) override;

protected:

	// パラメータ設定
	void SetParam() override;
};
