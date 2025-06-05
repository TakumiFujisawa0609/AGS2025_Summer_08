#pragma once
#include "SceneBase.h"

class T : public SceneBase
{

public:

	// コンストラクタ
	T(void);

	// デストラクタ
	~T(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:


	int tImg_;


};