#pragma once
class Stage;
class Camera;
class Player;
class PlayerShot;
class Blood;
class Enemy;
class EnemyShot;
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

	// ゲームクリアフラグの設定
	void SetIsGameClear(bool isGameClear);
	// ゲームクリアフラグの取得
	bool GetIsGameClear(void);

private:

	// ステージ
	Stage* stage_;

	// カメラ
	Camera* camera_;

	// プレイヤー
	Player* player_;

	// 敵
	Enemy* enemy_;

	// 弾
	PlayerShot* pShot_;

	// 敵の弾
	EnemyShot* eShot_;

	// 爆発
	Blood* blood_;

	// 衝突
	Collision* collision_;

	// ゲームオーバー画像ID
	int gameOverId_;
	// ゲームクリア画像ID
	int gameClearId_;

	// ゲームクリアフラグ
	bool isGameClear_;

	// プレイヤーの当たり判定の球体の半径
	float playerSphereRadius_;
	// 敵の当たり判定の球体の半径
	float enemySphereRadius_;
	// プレイヤーと敵の当たり判定用球体の半径の合計
	float radiusSum_;
	// 当たり判定用球体の中心間の距離
	float centerDistance_;
};
