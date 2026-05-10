#pragma once
#include <vector>
#include "../Common/Vector2.h"
#include "SceneBase.h"
class Button;

class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init() override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	Vector2 mousePos_;

	// testタイトル画像
	int testTitleImg_;

	// ボタン画像
	int normalGameStartImg_;
	int normalExitImg_;
	int hoverGameStartImg_;
	int hoverExitImg_;

	// ボタンの配列
	std::vector<Button*> buttons_;
};