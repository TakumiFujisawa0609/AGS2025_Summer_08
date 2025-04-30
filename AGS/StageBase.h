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


	//ステージの配置座標（ｚ）
	float stageLoopPosZ;
	//一つ目のステージ位置を変更する場合、true
	bool isLoopStage;


	//一つ目のステージモデルのロード
	int stageModeId;
	//2つ目ステージモデルのロード
	int stage2ModeId;
};

