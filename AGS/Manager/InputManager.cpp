#include "InputManager.h"

InputManager* InputManager::instance_ = nullptr;

InputManager::InputManager(void)
{
}

InputManager::~InputManager(void)
{
}

InputManager::InputManager(const InputManager& manager)
{
}

void InputManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new InputManager();
	}
}

InputManager* InputManager::GetInstance(void)
{
	if (instance_ == nullptr)
	{
		InputManager::CreateInstance();
	}
	return instance_;
}

void InputManager::DeleteInstance(void)
{
	if (instance_ != nullptr)
	{
		delete instance_;
	}
}

void InputManager::Init(void)
{
	// ゲームで使用したキーを、
	// 事前にここで登録しておく
	Add(KEY_INPUT_SPACE);
	Add(KEY_INPUT_W);
	Add(KEY_INPUT_S);
	Add(KEY_INPUT_A);
	Add(KEY_INPUT_D);
	Add(KEY_INPUT_UP);
	Add(KEY_INPUT_DOWN);
	Add(KEY_INPUT_LEFT);
	Add(KEY_INPUT_RIGHT);
	Add(KEY_INPUT_L);
	Add(MOUSE_INPUT_LEFT);
	Add(KEY_INPUT_R);


	// アニメーション用に使用するボタン
	Add(KEY_INPUT_1);
	Add(KEY_INPUT_2);
	Add(KEY_INPUT_3);
	Add(KEY_INPUT_4);
	Add(KEY_INPUT_5);
	Add(KEY_INPUT_6);

	// エフェクト用に使用するボタン
	Add(KEY_INPUT_Q);

}

void InputManager::Update(void)
{
	// 登録したキー情報をすべて
	for (int i = 0; i < keyInfos_.size(); ++i)
	{

		// 入力されたキーフレーム更新
		keyInfos_[i].keyOld = keyInfos_[i].keyNew;

		// ★ ここだけ条件分岐を追加（マウス用）
		if (keyInfos_[i].key >= MOUSE_INPUT_LEFT && keyInfos_[i].key <= MOUSE_INPUT_MIDDLE)
		{
			keyInfos_[i].keyNew = (GetMouseInput() & keyInfos_[i].key) != 0;
		}
		else
		{
			keyInfos_[i].keyNew = CheckHitKey(keyInfos_[i].key) != 0;
		}

		// 今押された(前フレームで押されてない＆今フレームがおされた)かをチェックして更新
		if (!keyInfos_[i].keyOld && keyInfos_[i].keyNew)
		{
			keyInfos_[i].keyTrgDown = true;
		}
		else
		{
			keyInfos_[i].keyTrgDown = false;
		}

		// 離された(前フレームでおされている＆今フレームでおされていない)
		if (keyInfos_[i].keyOld && !keyInfos_[i].keyNew)
		{
			keyInfos_[i].keyTrgUp = true;
		}
		else
		{
			keyInfos_[i].keyTrgUp = false;
		}
	}
}

void InputManager::Delete(void)
{
	// キー情報のstd::mapを削除する
	keyInfos_.clear();

	// インスタンスを削除する
	delete instance_;
}

void InputManager::Add(int key)
{
	InputManager::Info info;
	info.key = key;

	// キー判定初期化
	info.keyOld = false;
	info.keyNew = false;
	info.keyTrgDown = false;
	info.keyTrgUp = false;

	// キーと情報をセットにして登録する
	// キーから情報を取得出来るようにする
	keyInfos_.emplace(key, info);
}

void InputManager::Clear(void)
{
	keyInfos_.clear();
}

bool InputManager::IsNew(int key)
{
	InputManager::Info keyInfo = keyInfos_[key];
	return keyInfos_[key].keyNew;
}

bool InputManager::IsTrgDown(int key)
{
	InputManager::Info keyInfo = keyInfos_[key];
	return keyInfos_[key].keyTrgDown;
}

bool InputManager::IsTrgUp(int key)
{
	InputManager::Info keyInfo = keyInfos_[key];
	return keyInfos_[key].keyTrgUp;
}


