#pragma once
<<<<<<< HEAD

=======
#include <DxLib.h>
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
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

<<<<<<< HEAD
	int stageModeId_;

	//ステージ位置
	VECTOR stagePos_;

	VECTOR stageScale_;

};
=======

	//一つ目のステージモデルのロード
	int stageModeId_;

	// ステージの座標
	VECTOR stagePos_;

	// ステージのサイズ
	VECTOR stageScale_;
};

>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
