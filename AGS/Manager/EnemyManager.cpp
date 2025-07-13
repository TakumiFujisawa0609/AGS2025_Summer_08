#include <DxLib.h>
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyNormal.h"
#include "../Manager/ItemManager.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(Player* player, StageBase* stage, ItemManager* item)
{
	stage_ = stage;
	player_ = player;
	item_ = item;
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
			player_, stage_);

		// スポーン位置設定
		normal->SetPos(EnemyNormal::wave1SpawnPoints[i].pos);

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

	if (item_->GetPickdAllVaccine() && !isRespawn_)
	{
		ReSpawn();

		isRespawn_ = true;
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

void EnemyManager::ReSpawn()
{
	// 既存の敵を削除
	for (auto& pair : enemies_)
	{
		for (EnemyBase* enemy : pair.second)
		{
			enemy->Release();
			delete enemy;
		}
	}
	enemies_.clear();

	// WAVE2用の敵配置
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		EnemyBase* normal = new EnemyNormal();
		normal->Init(EnemyBase::TYPE::NORMAL,
			enemyModelIds_[static_cast<int>(EnemyBase::TYPE::NORMAL)],
			player_, stage_);

		normal->SetPos(EnemyNormal::wave2SpawnPoints[i].pos);
		enemies_[EnemyBase::TYPE::NORMAL].emplace_back(normal);
	}
}
 