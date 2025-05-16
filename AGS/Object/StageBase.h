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

private:

	//ステージモデルID
	int modelId_;

	//ステージ位置
	VECTOR Pos_;

	VECTOR Scale_;

};
