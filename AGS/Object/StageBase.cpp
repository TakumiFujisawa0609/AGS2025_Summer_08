#include "DxLib.h"
#include "StageBase.h"

StageBase::StageBase()
{
}

StageBase::~StageBase()
{
}

void StageBase::Init(void)
{

	//ステージモデルのロード
	modelId_ = MV1LoadModel("Data/Model/Stage/stage.mv1");

	//ステージのスケール
;
	//ステージ位置
	Pos_ = STAGE_POS;
	
	// ステージ設定
	MV1SetPosition(modelId_, Pos_);
}

void StageBase::Update(void)
{
	
}

void StageBase::Draw(void)
{
	// ステージモデル描画
	MV1DrawModel(modelId_);

	if (modelId_ == -1) {
		DrawFormatString(0, 300, 0xff0000, "モデル読み込み失敗！");
		return;
	}
}

void StageBase::Release(void)
{
	// ステージモデル解放
	MV1DeleteModel(modelId_);
}

int StageBase::GetModelId(void)
{
	return modelId_;
}
