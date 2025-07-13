#pragma once
#include <vector>
#include <map>
#include "../Object/Enemy/EnemyBase.h"
class EnemyBase;
class StageBase;
class Player;
class ItemManager;

class EnemyManager
{
public:

	static constexpr int ENEMY_NUM = 15;

	// コンストラクタ
	EnemyManager(Player* player, StageBase* stage, ItemManager* item);
	// デストラクタ
	~EnemyManager(void);
	void Init();
	void Update(void);
	void Draw(void);
	void Release(void);

	const std::map<EnemyBase::TYPE, std::vector<EnemyBase*>>& GetEnemies();

private:

	ItemManager* item_;

	// エネミー連想配列
	std::map<EnemyBase::TYPE, std::vector<EnemyBase*>> enemies_;

	// 敵用のモデルハンドルID
	std::vector<int> enemyModelIds_;

	StageBase* stage_;

	// プレイヤーのポインタ
	Player* player_;

	void ReSpawn();

	bool isRespawn_ = false;
};

