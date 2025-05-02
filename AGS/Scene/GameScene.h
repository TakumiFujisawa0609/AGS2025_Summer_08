#pragma once
#pragma once
class Stage;
class Camera;
class Player;
class PlayerShot;
class Blast;
class Enemy;
class Collision;


class GameScene
{

public:

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	// プレイヤー
	Player* player_;

	// ステージ
	Stage* stage_;

	// カメラ
	Camera* camera_;

	// 敵
	Enemy* enemy_;

	// 弾
	PlayerShot* pShot_;

	// 爆発
	Blast* blast_;

	// 衝突
	Collision* collision_;


};
