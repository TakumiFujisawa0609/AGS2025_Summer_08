#pragma once

class Player
{
public:
	static constexpr VECTOR DEFAULT_POS = { 0.0f,0.0f,0.0f };
	static constexpr VECTOR DEFAULT_ANGLE = { 0.0f,0.0f,0.0f };
	static constexpr float MOVE_SPEED = 10.0f;

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void Dir();
	void Move();

	VECTOR GetPPos(void);
private:

	// プレイヤーモデル
	int modelId_;

	// プレイヤー座標
	VECTOR pos_;
	// 角度
	VECTOR angle_;

	// 向き
	VECTOR moveDir_;
};