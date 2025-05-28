#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"
#include "../Object/Player.h"

void Player::Init(void)
{
	pos_ = { 0.0f, 0.0f, 0.0f };
	MV1SetPosition(modelId_, pos_);

	// 移動ベクトル初期化
	moveVec_ = AsoUtility::VECTOR_ZERO;

	// モデルの角度設定
	rot_ = { 0.0f, 0.0f, 0.0f };
	// モデルの角度
	localRot_ = INIT_MODEL_ROT_OFFSET;

	// カメラアングル
	cameraAngle_ = { 0.0f, 0.0f, 0.0f };
}

void Player::Update(VECTOR angle)
{
	// カメラアングル取得
	cameraAngle_ = angle;

	// 移動方向処理
	Dir();
	// 移動処理
	ProcessMove(cameraAngle_);
	//SetRotation();
}

void Player::Draw(void)
{

	//VECTOR startPos = VAdd(playerPos_, VGet(0.0f, 30.0f, 0));                          // 敵の座標
	//VECTOR endPos = VAdd(playerPos_, VGet(0.0f, 160.0f, 0));  // カプセルの上端（高さ60の例）
	float radius = 45.0f;	// 半径45（調整可）

	VECTOR centerPos = VAdd(pos_, VGet(0.0f, 110, 0));

	DrawSphere3D(centerPos, radius, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);	// 球を描画

	// プレイヤー座標
	DrawFormatString(0, 40, 0xffffff, "playerPos:(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
}

void Player::Release(void)
{
	
}

// プレイヤーの移動方向を決める
void Player::Dir()
{
	// 移動方向を決める
	moveVec_ = AsoUtility::VECTOR_ZERO;
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_W)) { moveVec_ = VAdd(moveVec_, AsoUtility::DIR_F); }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_S)) { moveVec_ = VAdd(moveVec_, AsoUtility::DIR_B); }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_D)) { moveVec_ = VAdd(moveVec_, AsoUtility::DIR_R); }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_A)) { moveVec_ = VAdd(moveVec_, AsoUtility::DIR_L); }
}

VECTOR Player::GetPPos(void)
{
	return pos_;
}

void Player::SetRotation(void)
{
	// 回転行列を使用した角度設定
	// ---------------------------
	// 単位行列を設定する
	MATRIX mat = MGetIdent();

	// モデル自体のY軸回転行列を作成する
	MATRIX mGetRotY = MGetRotY(rot_.y);

	// モデルの補正用Y軸回転行列を作成する
	MATRIX mGetLocalRotY = MGetRotY(localRot_.y);

	// 行列を合成
	mat = MMult(mat, mGetRotY);
	mat = MMult(mat, mGetLocalRotY);

	// 行列を使用してモデルの角度を設定
	MV1SetRotationMatrix(modelId_, mat);
}

// 移動処理
void Player::ProcessMove(VECTOR angle)
{
	// 移動方向を決める
	moveVec_ = AsoUtility::VECTOR_ZERO;
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_S)) { moveVec_ = VAdd(moveVec_, AsoUtility::DIR_F); }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_W)) { moveVec_ = VAdd(moveVec_, AsoUtility::DIR_B); }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_A)) { moveVec_ = VAdd(moveVec_, AsoUtility::DIR_R); }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_D)) { moveVec_ = VAdd(moveVec_, AsoUtility::DIR_L); }

	// 移動処理
	// 動いていたら
	if (!AsoUtility::EqualsVZero(moveVec_))
	{
		// カメラ角度分設定する
		MATRIX cameraMatY = MGetRotY(angle.y);
		moveVec_ = VTransform(moveVec_, cameraMatY);

		// 座標更新
		moveVec_ = VNorm(moveVec_);
		moveVec_ = VScale(moveVec_, MOVE_SPEED);
		pos_ = VAdd(pos_, moveVec_);

		// 方向を角度に変換する(XZ平面　Y軸)
		moveVecRad_.y = atan2f(moveVec_.x, moveVec_.z);

		// 計算角度を設定
		rot_.y = moveVecRad_.y;

		// 座標設定
		MV1SetPosition(modelId_, pos_);
	}

	//MV1SetRotationXYZ(modelId_, angle_);
}



