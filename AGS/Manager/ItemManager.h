#pragma once
#include <vector>
#include <map>
#include "../Object/Item/ItemBase.h"
class ItemBase;

class ItemManager
{
public:

	// アイテムの数
	static constexpr int BULLET_NUM = 0;
	static constexpr int KIT_NUM = 2;
	static constexpr int VACCINE_NUM = 3;

	// コンストラクタ・デストラクタ
	ItemManager(void);
	~ItemManager(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	const std::map<ItemBase::TYPE, std::vector<ItemBase*>>& GetItems();

private:

	// アイテム連想配列
	std::map<ItemBase::TYPE, std::vector<ItemBase*>> items_;

	// アイテム用モデルハンドルID
	std::vector<int> itemModelIds_;
};
