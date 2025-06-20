#include "DxLib.h"
#include "../Manager/Application.h"
#include "../Utility/AsoUtility.h"
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
	modelId_ = MV1LoadModel("Data/Model/Stage/Stage.mv1");
	dModelId_ = MV1LoadModel("Data/Model/Stage/Door/Door.mv1");


	// コリジョン情報の初期化
	MV1SetupCollInfo(modelId_, -1);

	//ステージのスケール
;
	//ステージ位置
	Pos_ = STAGE_POS;
	scale_ = { 1.0, 1.0, 1.0 };
	
	// ステージ設定
	MV1SetPosition(modelId_, Pos_);
	MV1SetScale(modelId_, scale_);

	// エミッシブカラー設定
	MV1SetMaterialEmiColor(modelId_, 0, GetColorF(0.5f , 0.5f, 0.5f, 1.0f)); // 内壁
	MV1SetMaterialEmiColor(modelId_, 1, GetColorF(0.5f, 0.5f, 0.5f, 1.0f));	// 外壁
	MV1SetMaterialEmiColor(modelId_, 2, GetColorF(0.5f, 0.5f, 0.5f, 1.0f));	// 追加した外壁2
	MV1SetMaterialEmiColor(modelId_, 3, GetColorF(0.5f, 0.5f, 0.5f, 1.0f));	// 追加した外壁1
	MV1SetMaterialEmiColor(modelId_, 4, GetColorF(0.5f, 0.5f, 0.5f, 1.0f));	// 最初の部屋の外壁
	MV1SetMaterialEmiColor(modelId_, 5, GetColorF(0.5f, 0.5f, 0.5f, 1.0f));	// 天井
	MV1SetMaterialEmiColor(modelId_, 6, GetColorF(0.5f, 0.5f, 0.5f, 1.0f));	// 台座

	dPos_ = { -1432,-3,50 };
	// ドア
	MV1SetPosition(dModelId_, dPos_);
	MV1SetScale(dModelId_, {0.85, 0.66, 1});
	MV1SetRotationXYZ(dModelId_, {0,  AsoUtility::Deg2RadF(90.0f), 0 });

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
