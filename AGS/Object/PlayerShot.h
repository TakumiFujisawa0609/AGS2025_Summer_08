#pragma once
class Camera;

class PlayerShot
{
public:
	static constexpr VECTOR DEFAULT_POS = { 0,0,0 };
	static constexpr VECTOR DEFAULT_SCALE = { 0.05f,0.05f,0.05f };

	static constexpr float SHOT_SPEED = 50.0f;

	static constexpr float P_SHOT_MOVE_LIMIT = 4000.0f;

	// 最大球数
	static constexpr int MAX_AMMO = 21;

	PlayerShot();
	~PlayerShot();
	void Init(Camera* camera);
	void Update(void);
	void Draw(void);
	void Release(void);

	void Shot(void);
	void ReLoad(void);

	int GetModelId() const;
	VECTOR GetPos();
	VECTOR GetDir();

	bool GetAlive(void);
	void SetAlive(bool isAlive);

	// マガジン取得
	void SetMagazine(int magazine);

private:
	Camera* camera_;

	// モデルID
	int modelId_;
	// 弾画像
	int image_;

	// 大きさ
	VECTOR scale_;

	VECTOR pos_;
	// 発射地点
	VECTOR startPos_;
	// 向き
	VECTOR dir_;

	float dist_;

	bool isAlive_;

	// マガジン数
	int magazine_;

	// 弾数
	int ammo_;
};

