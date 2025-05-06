#pragma once
#include <vector>
class GameScene;
class Camera;


class EnemyBase
{


public:
	static constexpr VECTOR INIT_ENEMY_POS = {500,250,-300};
	static constexpr VECTOR INIT_ENEMY_SCALE = {1.0f,1.0f,1.0f};


	void Init(GameScene* gameScene, Camera* camera);
	void Update(void);
	void Draw(void);
	void Release(void);

	VECTOR GetEnemyPos(void);

	// 敵の生存判定の設定
	void SetIsAliveEnemy(bool isAliveEnemy);
	// 敵の生存判定を取得
	bool GetIsAliveEnemy(void);

private:

	GameScene* gameScene_; // ゲームシーンのインスタンス
	Camera* camera_; // カメラのインスタンス

	// 敵モデルID
	int enemyModelId_;

	// 敵座標
	VECTOR enemyPos_;
	// 敵の大きさ
	VECTOR enemyScale_;
	// 敵の生存判定
	bool isAliveEnemy_;

	// アニメーション
	int animIndex_;

};

