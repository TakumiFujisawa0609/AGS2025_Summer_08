#pragma once
#include <DxLib.h>

class StageBase
{
public:
	StageBase();
	~StageBase();
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	int stageModeId_;

	//ステージ位置
	VECTOR stagePos_;

	VECTOR stageScale_;

};
