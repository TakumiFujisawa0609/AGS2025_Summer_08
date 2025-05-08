#include "StageBase.h"
#include "DxLib.h"

StageBase::StageBase()
{
}

StageBase::~StageBase()
{
}

void StageBase::Init(void)
{
<<<<<<< HEAD

	//ステージモデルのロード




	//ステージのスケール
;
	//ステージ位置
=======
	//ステージモデルのロード


	//ステージの拡大
	MV1SetScale(stageModeId_, stageScale_);
	//ステージ位置
	MV1SetPosition(stageModeId_, stagePos_);
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70

}

void StageBase::Update(void)
{
<<<<<<< HEAD
	
=======

>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
}

void StageBase::Draw(void)
{
}

void StageBase::Release(void)
{
}
