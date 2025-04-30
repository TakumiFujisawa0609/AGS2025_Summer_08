#include "StageBase.h"
#include "DxLib.h"
//A

StageBase::StageBase()
{
}

StageBase::~StageBase()
{
}

void StageBase::Init(void)
{
	//ステージ拡大サイズ設定
	VECTOR stageScalePos;
	//ステージ位置
	VECTOR stagePos;

	//２つ目ステージ拡大サイズ設定
	VECTOR stage2ScalePos;
	//２つ目ステージ位置
	VECTOR stage2Pos;



	stageScalePos = VGet(10.0f, 10.0f, 10.0f);
	//ステージ位置
	stagePos = VGet(0.0f, -50.0f, 0.0f);


	//２つ目ステージ拡大サイズ設定
	stage2ScalePos = VGet(10.0f, 10.0f, 10.0f);
	//２つ目ステージ位置
	stage2Pos = VGet(0.0f, -50.0f, 8000.0f);

	stageLoopPosZ = 8000.0f;

	isLoopStage = true;

	//一つ目のステージモデルのロード
	stageModeId = MV1LoadModel("Model/Stage.mv1");
	//2つ目ステージモデルのロード
	stage2ModeId = MV1LoadModel("Model/Stage.mv1");



	//ステージの拡大
	MV1SetScale(stageModeId, stageScalePos);
	//ステージ位置
	MV1SetPosition(stageModeId, stagePos);

	//ステージ2の拡大
	MV1SetScale(stage2ModeId, stage2ScalePos);
	//ステージ位置
	MV1SetPosition(stage2ModeId, stage2Pos);
}

void StageBase::Update(void)
{
	//ステージループ
	if (cameraPos.z > stageLoopPosZ)
	{

		//座標を奥に移動
		stageLoopPosZ += 8000.0f;
		if (isLoopStage)
		{
			//一つ目のステージ位置変更
			MV1SetPosition(stageModeId, stagePos = VGet(stagePos.x, stagePos.y, stageLoopPosZ));
			isLoopStage = false;
		}
		else
		{
			//二つ目のステージ位置変更
			MV1SetPosition(stage2ModeId, stage2Pos = VGet(stage2Pos.x, stage2Pos.y, stageLoopPosZ));
			isLoopStage = true;

		}
	}
}

void StageBase::Draw(void)
{
}

void StageBase::Release(void)
{
}
