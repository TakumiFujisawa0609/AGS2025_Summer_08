#include <DxLib.h>
#include "SoundManager.h"
#include "../Object/Item/ItemBase.h"
#include "../Object/Item/ItemBullet.h"
#include "../Object/Item/ItemKit.h"
#include "../Object/Item/ItemVaccine.h"
#include "../Object/Player.h"
#include "../Object/PlayerShot.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init(Player* player, PlayerShot* pShot)
{
	player_ = player;
	pShot_ = pShot;

	// アイテムモデルロード
	itemModelIds_.emplace_back(
		MV1LoadModel("Data/Model/Item/AmmoBox.mv1"));
	itemModelIds_.emplace_back(
		MV1LoadModel("Data/Model/Item/Kit.mv1"));
	itemModelIds_.emplace_back(
		MV1LoadModel("Data/Model/Item/vaccine.mv1"));

	// 決められた数配置
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// 弾生成
		ItemBase* bullet = new ItemBullet();

		//初期化　
		bullet->Init(ItemBase::TYPE::BULLET,
			itemModelIds_[static_cast<int>(ItemBase::TYPE::BULLET)]);

		// スポーン位置設定
		bullet->SetPos(ItemBullet::bulletSpawnPoints[i].pos);

		// アイテムを登録
		items_[ItemBase::TYPE::BULLET].emplace_back(bullet);

		// 弾薬箱をカウント
		bulletBoxNum_++;
	}

	//// 決められた数配置
	//for (int i = 0; i < VACCINE_NUM; i++)
	//{
	//	// 弾生成
	//	ItemBase* vaccine = new ItemVaccine();

	//	//初期化　
	//	vaccine->Init(ItemBase::TYPE::VACCINE,
	//		itemModelIds_[static_cast<int>(ItemBase::TYPE::VACCINE)]);

	//	// スポーン位置設定
	//	vaccine->SetPos(ItemVaccine::vaccineSpawnPoints[i].pos);

	//	// アイテムを登録
	//	items_[ItemBase::TYPE::VACCINE].emplace_back(vaccine);

	//	// ワクチンの数をカウント
	//	vaccineNum++;
	//}

	// 決められた数配置
	for (int i = 0; i < KIT_NUM; i++)
	{
		// 弾生成
		ItemBase* kit = new ItemKit();

		//初期化　
		kit->Init(ItemBase::TYPE::KIT,
			itemModelIds_[static_cast<int>(ItemBase::TYPE::KIT)]);

		// スポーン位置設定
		kit->SetPos(ItemKit::kitSpawnPoints[i].pos);

		// アイテムを登録
		items_[ItemBase::TYPE::KIT].emplace_back(kit);

		// 弾薬箱をカウント
		kitBoxNum_++;
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

	// ワクチンがすべて拾われていない場合は
	if (vaccineNum_ > 0)
	{
		DrawFormatString(0, 50, 0xffffff, "ワクチンを回収");
	}
	// ワクチンがすべて拾われたら
	else if(vaccineNum_ == 0)
	{
		DrawFormatString(0, 50, 0xffffff, "ドアから脱出");
	}

	// 最初のワクチン取得時に
	if (vaccineNum_ == 2)
	{
		// 今の時間を保存
		int now = GetNowCount();
		if (now - pickUpTime_ <= SHOW_DURATION)
		{
			// 拾ってから3秒以内なら画像表示
			DrawRotaGraph(955, 540, 0.5, 0, vImage_, true);
		}
	}

	// // ワクチンの現在数
	//DrawFormatString(0, 60, 0xffffff, "ワクチン残り個数:%d", vaccineNum_);

	if (pickedVaccineNum_ < 3)
	{
		// ワクチンの現在数
		DrawFormatString(0, 100, 0xffffff, "ワクチンを回収:%d", pickedVaccineNum_);
	}

	//// 弾薬箱の現在数
	//DrawFormatString(0, 80, 0xffffff, "弾薬箱残り個数:%d", bulletBoxNum_);

	//// 救急箱の現在数
	//DrawFormatString(0, 100, 0xffffff, "救急箱残り個数:%d", kitBoxNum_);
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

	DeleteGraph(vImage_);
}

// ワクチンを拾う
void ItemManager::PickVaccine(void)
{
	// ワクチンの数を減らす
	vaccineNum_--;

	// 取得ワクチンを増やす
	pickedVaccineNum_++;

	// ワクチンの数がマイナスにならないようにする
	if (vaccineNum_ < 0)
	{
		vaccineNum_ = 0;
	}

	// 取得音再生
	SoundManager::GetInstance()->PlayPickUp();
}

void ItemManager::PickBulletBox(void)
{
	// 弾薬箱の数を減らす
	bulletBoxNum_--;

	// 弾薬箱の数がマイナスにならないようにする
	if (bulletBoxNum_ < 0)
	{
		bulletBoxNum_ = 0;
	}

	// 取得音再生
	SoundManager::GetInstance()->PlayPickUp();

	// マガジンを１つ増やす
	pShot_->SetMagazine();
}

void ItemManager::PickKitBox(void)
{
	// 救急箱の数を減らす
	kitBoxNum_--;

	// 救急箱の数がマイナスにならないようにする
	if (kitBoxNum_ < 0)
	{
		kitBoxNum_ = 0;
	}

	// 取得音再生
	SoundManager::GetInstance()->PlayPickUp();

	// プレイヤーの体力を回復可能数を増やす
	player_->Heal(1);
}

int ItemManager::GetVaccine(void)
{
	return vaccineNum_;
}

const std::map<ItemBase::TYPE, std::vector<ItemBase*>>& ItemManager::GetItems()
{
	return items_;
}
