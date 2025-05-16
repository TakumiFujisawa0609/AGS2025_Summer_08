#pragma once
#include "../Function/AnimControl.h"
class Player;

enum EnemyState
{
	STATE_IDLE,		// 待機
	STATE_WALK,		// 歩き
	STATE_RUN,		// 走り
	STATE_ATTACK,	// 攻撃
	STATE_DIE,		// 死亡
};;

class EnemyBase
{
public:

	// 敵初期位置
	static constexpr VECTOR INIT_ENEMY_POS = { 0.0f, 0.0f, 250.0f };
	// 敵初期角度
	static constexpr VECTOR INIT_ENEMY_ANGLE = { 0.0f, 0.0f, 0.0f };

	// 移動速度
	static constexpr float MOVE_WALK_SPEED = 2.0f;	// 歩き
	static constexpr float MOVE_RUN_SPEED = 4.0f;	// 走り

	// アニメーションが切り替わる距離
	static constexpr float WALK_DISTANCE = 1200.0f;	// 歩き
	static constexpr float RUN_DISTANCE = 600.0f;	// 走り
	static constexpr float ATTACK_DISTANCE = 150.0f;	// 攻撃


	void Init(Player* player);	// 初期化
	void Update();	// 更新
	void Draw();	// 描画
	void Release();	// 解放

	void ChangeAnim();	// アニメーション変更
	void ChacePlayer();	// プレイヤー追尾

private:

	AnimControl* anim_;	// アニメーションクラス
	EnemyState state_;	// 敵の状態

	Player* player_;	// プレイヤーのポインタ

	// 敵モデルID
	int modelId_;

	// 敵座標
	VECTOR pos_;
	// 敵角度
	VECTOR angle_;
	// 敵のスピード
	float speed_;

	// 敵とプレイヤーの距離
	float dist_ = 0.0f;

};
