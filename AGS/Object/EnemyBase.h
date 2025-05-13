#pragma once

enum EnemyAnimType
{
	Idle,	// 待機
	Walk,	// 歩く
	Run,	// 走る
	Attack,	// 攻撃
	Die,	// 死亡
	MAX,	// 配列のサイズ
};

class EnemyBase
{
public:

	// 敵初期位置
	static constexpr VECTOR INIT_ENEMY_POS = { 0.0f, 0.0f, 250.0f };
	// 敵初期角度
	static constexpr VECTOR INIT_ENEMY_ANGLE = { 0.0f, 0.0f, 0.0f };

	void Init();	// 初期化
	void Update();	// 更新
	void Draw();	// 描画
	void Release();	// 解放



private:

	// 敵モデルID
	int enemyModelId_;

	VECTOR enemyPos_;

	// 敵角度
	VECTOR enemyAngle_;

	int attachAnimIndex_;      // アニメーションのアタッチインデックス
	float animTime_;           // 再生時間
	float animTotalTime_;      // アニメーション全体の長さ
};
