#pragma once
#include <vector>
#include <map>
#include "../Object/Item/ItemBase.h"
class ItemBase;
class Player;
class PlayerShot;

class ItemManager
{
public:

	// アイテムの数
	static constexpr int BULLET_NUM = 5;
	static constexpr int KIT_NUM = 2;
	static constexpr int VACCINE_NUM = 3;

	static constexpr int SHOW_DURATION = 2500;

	// コンストラクタ・デストラクタ
	ItemManager(void);
	~ItemManager(void);

	void Init(Player* player, PlayerShot* pShot);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ワクチンを取得
	void PickVaccine(void);

	// 弾薬箱を取得
	void PickBulletBox(void);

	// 救急箱を取得
	void PickKitBox(void);


	// ワクチンの数を取得
	int GetVaccine(void);

	const std::map<ItemBase::TYPE, std::vector<ItemBase*>>& GetItems();

private:

	Player* player_; // プレイヤーへのポインタ
	PlayerShot* pShot_; // 弾へのポインタ

	// アイテム連想配列
	std::map<ItemBase::TYPE, std::vector<ItemBase*>> items_;

	// アイテム用モデルハンドルID
	std::vector<int> itemModelIds_;

	// ワクチンの数
	int vaccineNum_;
	// 取得ワクチン
	int pickedVaccineNum_ = 0;

	// 弾薬箱の数
	int bulletBoxNum_;

	// 救急箱の数
	int kitBoxNum_;

	int vImage_;
	int pickUpTime_ = 0;   // 拾った時間（ミリ秒）


	bool task01_Alive;
	bool task02_Alive;
	bool task03_Alive;
	bool task04_Alive;
	bool lasttask_Alive;


	int task_01;
	int task_02;
	int task_03;
	int task_04;
	int lastTask;
};
