#pragma once

class Player
{
public:

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// プレイヤーモデル
	int playerModelId_;
};