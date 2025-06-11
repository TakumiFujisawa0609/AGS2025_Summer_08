#include "DxLib.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/SoundManager.h"
#include "T.h"

T::T(void)
{
}

T::~T(void)
{
}

void T::Init(void)
{
	tImg_ = LoadGraph("Data/Image/Operation.png");
}

void T::Update(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);

		SoundManager::GetInstance()->PlayClose();
	}
}

void T::Draw(void)
{
	float scale = 1.0f;  // 縮小
	DrawRotaGraph(958, 538, scale, 0.0f, tImg_, true);
}

void T::Release(void)
{
	DeleteGraph(tImg_);
}
