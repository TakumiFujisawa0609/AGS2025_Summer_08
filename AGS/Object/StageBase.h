#pragma once
#include <DxLib.h>

class StageBase
{
public:
	// ステージ座標
	static constexpr VECTOR STAGE_POS = { 0.0f, 0.0f, 0.0f };

	StageBase();
	~StageBase();
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	int GetModelId(void);
	VECTOR GetDPos(void);

private:

	//ステージモデルID
	int modelId_;

	// ドア
	int dModelId_;

	//ステージ位置
	VECTOR Pos_;

	VECTOR scale_;

	//ドア位置
	VECTOR dPos_;

	VECTOR dScale_;
	VECTOR dAngle_;

	//virtual void SetParam();

};
