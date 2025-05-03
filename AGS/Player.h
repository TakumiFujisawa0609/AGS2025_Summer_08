#pragma once

class Player
{
public:

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void SetPlayerPos(VECTOR playerPos);
	VECTOR GetPlayerPos(void);

private:

	int playerModelId_;

	VECTOR playerPos_;
};
