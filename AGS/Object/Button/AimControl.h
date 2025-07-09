#pragma once
#include <vector>

class AimButton;

class AimControl
{

public:
	AimControl(void);
	~AimControl(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//ブロックアクションのgameSceneを参照する

private:

	std::vector<AimButton*> aimButtons_;
};


