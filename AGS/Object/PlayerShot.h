#pragma once
class Camera;

class PlayerShot
{
public:
	static constexpr VECTOR DEFAULT_POS = { 0,0,0 };
	static constexpr VECTOR DEFAULT_SCALE = { 0.05f,0.05f,0.05f };

	static constexpr float SHOT_SPEED = 50.0f;

	static constexpr float P_SHOT_MOVE_LIMIT = 4000.0f;

	// Å‘å‹…”
	static constexpr int MAX_AMMO = 12;

	PlayerShot();
	~PlayerShot();
	void Init(Camera* camera);
	void Update(void);
	void Draw(void);
	void Release(void);

	int GetModelId() const;
	VECTOR GetPos();
	VECTOR GetDir();

	bool GetAlive(void);
	void SetAlive(bool isAlive);

	void SetHave(bool isHave);

private:
	Camera* camera_;

	// ƒ‚ƒfƒ‹ID
	int modelId_;
	// ’e‰æ‘œ
	int image_;

	// ‘å‚«‚³
	VECTOR scale_;

	VECTOR pos_;
	// ”­Ë’n“_
	VECTOR startPos_;
	// Œü‚«
	VECTOR dir_;

	float dist_;

	bool isAlive_;

	bool isHave_;

	// ’e”
	int ammo_;
};

