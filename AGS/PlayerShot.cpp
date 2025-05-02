#include <DxLib.h>
#include "PlayerShot.h"
#include "Player.h"

PlayerShot::PlayerShot()
{
}

PlayerShot::~PlayerShot()
{
}

void PlayerShot::Init(Player* player)
{
	player_ = player;	// プレイヤーのインスタンスを取得

	// 弾モデルの読み込み
	pShotModelId_ = MV1LoadModel("Data/Model/Shot.mv1");


	// 弾の座標の初期化
	pShotPos_ = INIT_P_SHOT_POS;

	// 弾の生存判定の初期化
	isAlivePShot_ = false;


}

void PlayerShot::Update()
{
	// プレイヤーの座標
	VECTOR playerPos = player_->GetPlayerPos();

	
}

void PlayerShot::Draw()
{
	


}

void PlayerShot::Release()
{
	// 弾モデルの解放
	MV1DeleteModel(pShotModelId_);
	MV1DeleteModel(abnormalPShotModelId1_);
	MV1DeleteModel(abnormalPShotModelId2_);
}










