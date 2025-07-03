#pragma once
#include "SceneBase.h"

class MovieScene : public SceneBase
{

public:

	// コンストラクタ
	MovieScene(void);

	// デストラクタ
	~MovieScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	int movieHandle_;

	float playTime_;         // 再生経過時間
	static constexpr float MOVIE_LENGTH = 6.1f;  // 動画の長さ（秒）
};