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
	//ステージモデルのロード


	//ステージの拡大
	MV1SetScale(stageModeId_, stageScale_);
	//ステージ位置
	MV1SetPosition(stageModeId_, stagePos_);

}

void StageBase::Update(void)
{

}

void StageBase::Draw(void)
{
}

void StageBase::Release(void)
{
}
