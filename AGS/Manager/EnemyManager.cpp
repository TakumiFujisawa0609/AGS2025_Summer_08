#include <DxLib.h>
#include "../Object/Player.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyNormal.h"
#include "../Object/Enemy/EnemyFemale.h"
#include "../Object/Enemy/EnemyPrisoner.h"
#include "../Manager/ItemManager.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(Player* player, StageBase* stage, ItemManager* item, Camera* camera)
{
	stage_ = stage;
	camera_ = camera;
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
	enemyModelIds_.emplace_back(
		MV1LoadModel("Data/Model/Enemy/FZombie.mv1"));
	enemyModelIds_.emplace_back(
		MV1LoadModel("Data/Model/Enemy/PZombie.mv1"));

	// 決められた数配置
	for (int i = 0; i < 13; i++)
	{
		// 敵生成
		EnemyBase* normal = new EnemyNormal();

		// 初期化
		normal->Init(EnemyBase::TYPE::NORMAL,
			enemyModelIds_[static_cast<int>(EnemyBase::TYPE::NORMAL)],
			player_, stage_, camera_);

		// スポーン位置設定
		normal->SetPos(EnemyNormal::wave1SpawnPoints[i].pos);

		// 敵を登録
		enemies_[EnemyBase::TYPE::NORMAL].emplace_back(normal);
	}

	// 決められた数配置
	for (int i = 0; i < 2; i++)
	{
		// 敵生成
		EnemyBase* prisoner = new EnemyPrisoner();

		// 初期化
		prisoner->Init(EnemyBase::TYPE::PRISONER,
			enemyModelIds_[static_cast<int>(EnemyBase::TYPE::PRISONER)],
			player_, stage_, camera_);

		// スポーン位置設定
		prisoner->SetPos(EnemyPrisoner::prisonerWave1SpawnPoints[i].pos);

		// 敵を登録
		enemies_[EnemyBase::TYPE::PRISONER].emplace_back(prisoner);
	}
}

void EnemyManager::Update(void)
{
	// すべての敵を更新
	for (auto& pair : enemies_) // ← const外す
	{
		auto& enemyList = pair.second;

		for (auto it = enemyList.begin(); it != enemyList.end(); )
		{
			EnemyBase* enemy = *it;
			enemy->Update();

			VECTOR pPos = player_->GetPPos();
			float dis = VSize(VSub(enemy->GetPos(), pPos));

			// 死んでいて、かつプレイヤーから離れたら削除
			if (!enemy->GetAlive() && dis > 1000 && !enemy->CanSeePlayer())
			{
				enemy->Release();
				delete enemy;
				it = enemyList.erase(it); // eraseしたら戻り値で次に進む
			}
			else
			{
				++it;
			}
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
	for (int i = 0; i < 10; i++)
	{
		EnemyBase* normal = new EnemyNormal();
		normal->Init(EnemyBase::TYPE::NORMAL,
			enemyModelIds_[static_cast<int>(EnemyBase::TYPE::NORMAL)],
			player_, stage_, camera_);

		normal->SetPos(EnemyNormal::wave2SpawnPoints[i].pos);
		enemies_[EnemyBase::TYPE::NORMAL].emplace_back(normal);
	}

	// 決められた数配置
	for (int i = 0; i < 2; i++)
	{
		// 敵生成
		EnemyBase* female = new EnemyFemale();

		// 初期化
		female->Init(EnemyBase::TYPE::FEMALE,
			enemyModelIds_[static_cast<int>(EnemyBase::TYPE::FEMALE)],
			player_, stage_, camera_);

		// スポーン位置設定
		female->SetPos(EnemyFemale::femaleWave2SpawnPoints[i].pos);

		// 敵を登録
		enemies_[EnemyBase::TYPE::FEMALE].emplace_back(female);
	}
}
 