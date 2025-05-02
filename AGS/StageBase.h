#pragma once
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


	//一つ目のステージモデルのロード
	int stageModeId_;

	// ステージの座標
	VECTOR stagePos_;

	// ステージのサイズ
	VECTOR stageScale_;
};

