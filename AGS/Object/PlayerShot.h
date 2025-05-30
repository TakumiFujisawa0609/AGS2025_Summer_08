#pragma once
class Camera;

class PlayerShot
{
public:
	static constexpr VECTOR DEFAULT_POS = { 0,0,0 };
	static constexpr VECTOR DEFAULT_SCALE = { 0.2f,0.2f,0.2f };

	static constexpr float SHOT_SPEED = 10.0f;

	static constexpr float P_SHOT_MOVE_LIMIT = 600.0f;

	PlayerShot();
	~PlayerShot();
	void Init(Camera* camera);
	void Update(void);
	void Draw(void);
	void Release(void);

	int GetModelId() const;
	VECTOR GetPos();
	VECTOR GetDir();
private:
	Camera* camera_;

	// ƒ‚ƒfƒ‹ID
	int modelId_;

	// ‘å‚«‚³
	VECTOR scale_;

	VECTOR pos_;
	// ”­ŽË’n“_
	VECTOR startPos_;
	// Œü‚«
	VECTOR dir_;

	float dist_;

	bool isAlive_;
};

