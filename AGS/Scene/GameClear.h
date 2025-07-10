#pragma once
#include "SceneBase.h"

class GameClear : public SceneBase
{

public:

	// コンストラクタ
	GameClear(void);

	// デストラクタ
	~GameClear(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	int gameClearImg_;
	int resultImg_;

	int clearMovieHundle_;

	float clearTime_;

	float movieTimer_;
	bool isPause_;

	bool isResult_;

	int fontHandle_;
};