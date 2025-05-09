#pragma once

class Player
{
public:

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPPos(void);
private:

	// プレイヤーモデル
	int playerModelId_;

	// プレイヤー座標
	VECTOR playerPos_;
};