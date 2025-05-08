#pragma once

class EnemyBase
{
public:
	static constexpr VECTOR INIT_ENEMY_POS = { 500.0f,300.0f,-400.0f };

	void Init();	// ‰Šú‰»
	void Update();	// XV
	void Draw();	// •`‰æ
	void Release();	// ‰ğ•ú

private:

	int enemyModelId_;

	VECTOR enemyPos_;
};