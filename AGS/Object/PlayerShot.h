#pragma once
#include <vector>
class Player;
class Camera;

class PlayerShot
{
public:

	struct ShotData {
		bool isAlive = false;
		VECTOR pos = { 0,0,0 };
		VECTOR startPos = { 0,0,0 };
		VECTOR dir = { 0,0,0 };
		float dist = 0.0f;
	};


	static constexpr VECTOR DEFAULT_POS = { 0,0,0 };
	static constexpr VECTOR DEFAULT_SCALE = { 0.05f,0.05f,0.05f };
	static constexpr float SHOT_SPEED = 60.0f;
	static constexpr float P_SHOT_MOVE_LIMIT = 4000.0f;
	static constexpr int MAX_AMMO = 20;
	static constexpr int MAX_SHOTS = 10; // 同時に飛ばせる弾数
	static constexpr int SHOT_INTERVAL = 25; // 発射間隔（フレーム）

	PlayerShot();
	~PlayerShot();
	void Init(Camera* camera, Player* player);
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

	std::vector<ShotData>& GetShots();

	// マガジン取得
	void SetMagazine();

private:
	Player* player_;
	Camera* camera_;

	int modelId_;
	int image_;
	int rKeyImg_;
	int gunCircleImg_;

	bool isReload_ = false;
	VECTOR scale_;
	int maxMagazine_;
	int ammo_;

	std::vector<ShotData> shots_;
	int shotTimer_ = 0;

	bool isReloading_ = false;     // リロード中フラグ
	float reloadTimer_ = 0.0f;     // リロード経過時間

};
