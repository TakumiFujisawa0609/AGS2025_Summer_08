#pragma once
#include "SceneBase.h"

class Tutorial : public SceneBase
{

public:

	// コンストラクタ
	Tutorial(void);

	// デストラクタ
	~Tutorial(void);
	 
	void Init(void) override;    // 初期化
	void Update(void) override;  // 更新処理
	void Draw(void) override;    // 描画処理
	void Release(void) override; // 解放処理

private:
	
	// チュートリアル画像
	int tutorialImg_;

};