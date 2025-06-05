#include <DxLib.h>
#include "../Object/Item/ItemBase.h"
#include "../Object/Item/ItemBullet.h"
#include "../Object/Item/ItemKit.h"
#include "../Object/Item/ItemVaccine.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init(void)
{
	// アイテムモデルロード
	itemModelIds_.emplace_back(
		MV1LoadModel("Data/Model/Item/AmmoBox.mv1"));
	itemModelIds_.emplace_back(
		MV1LoadModel("Data/Model/Item/Kit.mv1"));
	itemModelIds_.emplace_back(
		MV1LoadModel("Data/Model/Item/vaccine.mv1"));

	//// 決められた数配置
	//for (int i = 0; i < BULLET_NUM; i++)
	//{
	//	// 弾生成
	//	ItemBase* bullet = new ItemBullet();

	//	//初期化　
	//	bullet->Init(ItemBase::TYPE::BULLET,
	//		itemModelIds_[static_cast<int>(ItemBase::TYPE::BULLET)]);

	//	// スポーン位置設定
	//	bullet->SetPos(ItemBullet::bulletSpawnPoints[i].pos);

	//	// アイテムを登録
	//	items_[ItemBase::TYPE::BULLET].emplace_back(bullet);
	//}


	// 決められた数配置
	for (int i = 0; i < VACCINE_NUM; i++)
	{
		// 弾生成
		ItemBase* vaccine = new ItemVaccine();

		//初期化　
		vaccine->Init(ItemBase::TYPE::VACCINE,
			itemModelIds_[static_cast<int>(ItemBase::TYPE::VACCINE)]);

		// スポーン位置設定
		vaccine->SetPos(ItemVaccine::vaccineSpawnPoints[i].pos);

		// アイテムを登録
		items_[ItemBase::TYPE::VACCINE].emplace_back(vaccine);
	}

	//// 決められた数配置
	//for (int i = 0; i < KIT_NUM; i++)
	//{
	//	// 弾生成
	//	ItemBase* kit = new ItemKit();

	//	//初期化　
	//	kit->Init(ItemBase::TYPE::KIT,
	//		itemModelIds_[static_cast<int>(ItemBase::TYPE::KIT)]);

	//	// スポーン位置設定
	//	kit->SetPos(ItemKit::kitSpawnPoints[i].pos);

	//	// アイテムを登録
	//	items_[ItemBase::TYPE::KIT].emplace_back(kit);
	//}
}

void ItemManager::Update(void)
{
	
	// すべてのアイテムを更新
	for (const auto pair : items_)
	{
		for (ItemBase* item : pair.second)
		{
			item->Update();
		}
	}


}

void ItemManager::Draw(void)
{
	// すべてのアイテムを描画
	for (const auto pair : items_)
	{
		for (ItemBase* item : pair.second)
		{
			item->Draw();
		}
	}
}

void ItemManager::Release(void)
{
	// すべてのアイテムを解放
	for (const auto pair : items_)
	{
		for (ItemBase* item : pair.second)
		{
			item->Release();
			delete item;
		}
	}

	// ベースとなるモデルのメモリ解放
	for (int id : itemModelIds_)
	{
		MV1DeleteModel(id);
	}
}

const std::map<ItemBase::TYPE, std::vector<ItemBase*>>& ItemManager::GetItems()
{
	return items_;
}
