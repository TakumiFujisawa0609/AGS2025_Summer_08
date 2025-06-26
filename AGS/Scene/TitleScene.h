#pragma once
#include "SceneBase.h"



class Camera;
class Button;
class ExitButton;


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

	int mousePos_X;
	int mousePos_Y;

	// testタイトル画像
	int testTitleImg_;

	int gameText_;
	int tutorialText_;
	int frameImage_;

	// スタート画像
	Camera* camera_;
	Button* button_;
	ExitButton* exitButton_;


};