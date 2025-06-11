#include "DxLib.h"
#include "../../Manager/Application.h"
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
	dModelId_ = MV1LoadModel("Data/Model/Stage/Door/Door.mv1");


	// コリジョン情報の初期化
	MV1SetupCollInfo(modelId_, -1);

	//ステージのスケール
;
	//ステージ位置
	Pos_ = STAGE_POS;
	scale_ = { 1,1,1 };
	
	// ステージ設定
	MV1SetPosition(modelId_, Pos_);
	MV1SetScale(modelId_, scale_);

	dPos_ = { 0,-70,-754 };
	// ドア
	MV1SetPosition(dModelId_, dPos_);

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

	MV1DrawModel(dModelId_);

	VECTOR centerPos = dPos_;
	centerPos = VAdd(centerPos, VGet(0, 200, 0));

	//DrawSphere3D(centerPos, 170, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);

}

void StageBase::Release(void)
{
	// ステージモデル解放
	MV1DeleteModel(modelId_);

	MV1DeleteModel(dModelId_);
}

int StageBase::GetModelId(void)
{
	return modelId_;
}

VECTOR StageBase::GetDPos(void)
{
	return dPos_;
}
