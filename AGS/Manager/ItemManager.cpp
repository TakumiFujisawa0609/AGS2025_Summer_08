#include <DxLib.h>
#include "SoundManager.h"
#include "../Object/Item/ItemBase.h"
#include "../Object/Item/ItemBullet.h"
#include "../Object/Item/ItemKit.h"
#include "../Object/Item/ItemVaccine.h"
#include "../Object/Player.h"
#include "../Object/PlayerShot.h"
#include "ItemManager.h"
#include "../Manager/InputManager.h"

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

	task_01 = LoadGraph("Data/Image/Task/Task_01.png");
	task_02 = LoadGraph("Data/Image/Task/Task_02.png");
	task_03 = LoadGraph("Data/Image/Task/Task_03.png");
	task_04 = LoadGraph("Data/Image/Task/Task_04.png");
	lastTask = LoadGraph("Data/Image/Task/LastTask.png");


	 task01_Alive = true;
	 task02_Alive = true;
	 task03_Alive = true;
	 task04_Alive = true;
	 lasttask_Alive = false;
	
	 hasPlayed = true;
	 countPlay = true;

	 count_span = 0;

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

		// ワクチンの数をカウント
		vaccineNum_++;
	}

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
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_2))
	{
		pickedVaccineNum_ = pickedVaccineNum_ + 1;
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

	

	//獲得ワクチンが0個
	if (pickedVaccineNum_ == 0)
	{
		DrawExtendGraph(0, 100, 400, 200, task_01, true);
	}
	//獲得ワクチンが１個
	if (pickedVaccineNum_ == 1)
	{

		if (task01_Alive == true)
		{
			task01_Alive = false;
			SoundManager::GetInstance()->PlayCount();
			
		}
		DrawExtendGraph(0, 100, 400, 200, task_02, true);
	}

	//獲得ワクチンが2個
	if (pickedVaccineNum_ == 2)
	{
		
		if (task02_Alive == true)
		{
			SoundManager::GetInstance()->PlayCount();
			task02_Alive = false;
		}
		DrawExtendGraph(0, 100, 400, 200, task_03, true);
	}

	if (lasttask_Alive == false)
	{
		//獲得ワクチンが3個
		if (pickedVaccineNum_ == 3)
		{
			if (task03_Alive == true)
			{
				SoundManager::GetInstance()->PlayCount();
				task03_Alive = false;
			}
			
			DrawExtendGraph(0, 100, 400, 200, task_04, true);
			count_span++;
		}
	}
	//最後のタスク表示するまでのカウント
	if (count_span >= LAST_COUNT_SPAN)
	{
		lasttask_Alive = true;
	}

	//最後のタスク表示
	if(	lasttask_Alive == true)
	{
		count_span = 0;
		if (hasPlayed == true)
		{
			SoundManager::GetInstance()->PlayCount();
			hasPlayed = false;
		}

		DrawExtendGraph(0,100, 400, 200, lastTask, true);
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
