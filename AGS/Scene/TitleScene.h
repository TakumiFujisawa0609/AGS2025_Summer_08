#pragma once
#include "SceneBase.h"
<<<<<<< HEAD
=======

class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// タイトル画像
	int testTitle_;

	// スタート画像
	

};
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70


class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// testタイトル画像
	int testTitleImg_;

	// スタート画像


};