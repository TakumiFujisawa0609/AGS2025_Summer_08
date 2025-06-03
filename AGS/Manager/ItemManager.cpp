#include <DxLib.h>
#include "../Object/Item/ItemBase.h"
#include "../Object/Item/ItemBullet.h"
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
		MV1LoadModel(""));
	
	// 決められた数配置
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// 弾生成
		ItemBase* bullet = new ItemBullet();

		//初期化　
		bullet->Init(ItemBase::TYPE::BULLET,
			itemModelIds_[static_cast<int>(ItemBase::TYPE::BULLET)]);

		// スポーン位置設定
		bullet->SetPos(ItemBullet::spawnPoints[i].pos);

		// アイテムを登録
		items_[ItemBase::TYPE::BULLET].emplace_back(bullet);
	}
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
