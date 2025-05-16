#pragma once
#include "SceneBase.h"
class Camera;

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

	Camera* camera_;

};