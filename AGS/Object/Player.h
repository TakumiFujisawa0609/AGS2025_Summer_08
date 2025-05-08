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

<<<<<<< HEAD
	// プレイヤーモデル
	int playerModelId_;
};
=======
	int playerModelId_;

	VECTOR playerPos_;
};
>>>>>>> 1320b2c2663e97c41eb8fd77b67b0acd9567dc70
