#include <DxLib.h>
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyNormal.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(Player* player)
{
	player_ = player;
}

EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::Init()
{
	// 敵モデルのロード
	enemyModelIds_.emplace_back(
		MV1LoadModel("Data/Model/Enemy/Zombie.mv1"));

	// 決められた数配置
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// 敵生成
		EnemyBase* normal = new EnemyNormal();

		// 初期化
		normal->Init(EnemyBase::TYPE::NORMAL,
			enemyModelIds_[static_cast<int>(EnemyBase::TYPE::NORMAL)],
			player_);

		// スポーン位置設定
		normal->SetPos(EnemyNormal::spawnPoints[i].pos);

		// 敵を登録
		enemies_[EnemyBase::TYPE::NORMAL].emplace_back(normal);
	}
}

void EnemyManager::Update(void)
{
	// すべての敵を更新
	for (const auto pair : enemies_)
	{
		for (EnemyBase* enemy : pair.second)
		{
			enemy->Update();
		}
	}
}

void EnemyManager::Draw(void)
{
	for (const auto pair : enemies_)
	{
		for (EnemyBase* enemy : pair.second)
		{
			enemy->Draw();
		}
	}
}

void EnemyManager::Release(void)
{
	for (const auto pair : enemies_)
	{
		for (EnemyBase* enemy : pair.second)
		{
			enemy->Release();
			delete enemy;
		}
	}

	// ベースとなるモデルのメモリ解放
	for (int id : enemyModelIds_)
	{
		MV1DeleteModel(id);
	}
}

const std::map<EnemyBase::TYPE, std::vector<EnemyBase*>>& EnemyManager::GetEnemies()
{
	return enemies_;
}
 