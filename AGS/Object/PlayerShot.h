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
	static constexpr int MAX_AMMO = 20;

	PlayerShot();
	~PlayerShot();
	void Init(Camera* camera);
	void Update(void);
	void Draw(void);
	void Release(void);

	void Shot(void);
	void ReLoad(void);

	void KeyDraw(void);

	int GetModelId() const;
	VECTOR GetPos();
	VECTOR GetDir();

	bool GetAlive(void);
	void SetAlive(bool isAlive);

	// マガジン取得
	void SetMagazine();

private:
	Camera* camera_;

	// モデルID
	int modelId_;
	// 弾画像
	int image_;

	// キー画像
	int rKeyImg_;
	// リロードフラグ
	bool isReload_ = false;

	// 大きさ
	VECTOR scale_;

	VECTOR pos_;
	// 発射地点
	VECTOR startPos_;
	// 向き
	VECTOR dir_;

	// 距離
	float dist_;

	bool isAlive_;

	// 最大弾数
	int maxMagazine_;

	// 弾数
	int ammo_;

	// 弾
	int gunCircleImg_;
};

