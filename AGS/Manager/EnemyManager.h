#pragma once
#include <vector>
#include <map>
#include "../Object/Enemy/EnemyBase.h"
class EnemyBase;
class Player;

class EnemyManager
{
public:

	static constexpr int ENEMY_NUM = 2;

	// コンストラクタ
	EnemyManager(Player* player);
	// デストラクタ
	~EnemyManager(void);
	void Init();
	void Update(void);
	void Draw(void);
	void Release(void);

	const std::map<EnemyBase::TYPE, std::vector<EnemyBase*>>& GetEnemies();

private:

	// エネミー連想配列
	std::map<EnemyBase::TYPE, std::vector<EnemyBase*>> enemies_;

	// 敵用のモデルハンドルID
	std::vector<int> enemyModelIds_;

	// プレイヤーのポインタ
	Player* player_;
};

