#pragma once

class Blood
{
public:
	// パーティクル要素
	struct Particle
	{
		VECTOR pos;
		VECTOR dir;
		float life;
		float scale;
		float speed;
	};
	
	static constexpr int PARTICLE_NUM = 40;
	static constexpr float MAX_LIFE = 1.0;
	static constexpr float SPEED = 3.0f;
	static constexpr float SCALE = 5.5f;


	void Init();	// 初期化
	void Update();	// 更新
	void Draw();	// 描画
	void Release();	// 解放

	void Emit();

	void SetPos(VECTOR pos);
	void SetAlive(bool isAlive);
private:

	// パーティクル
	Particle particles_[PARTICLE_NUM];
	// 発生元の中心位置
	VECTOR origin_; 

	// 画像ID
	int imageId_;
	// 生存判定
	bool isAlive_;
};
