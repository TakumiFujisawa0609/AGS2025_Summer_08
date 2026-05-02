#include "../../../Object/Common/AnimationController.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/Camera.h"
#include "../../../Manager/InputManager.h"
#include "../../../Manager/ResourceManager.h"
#include "../../Common/Transform.h"
#include "../../../Utility/AsoUtility.h"
#include "../../Collider/ColliderLine.h"
#include "../../Collider/ColliderCapsule.h"
#include "Player.h"


Player::Player(void)
	:
	CharactorBase(),
	isHealing_(false)
{
}

Player::~Player(void)
{
}

void Player::ProcessMove(void)
{
	auto& ins = InputManager::GetInstance();

	// 移動量
	movePow_ = AsoUtility::VECTOR_ZERO;
	// 方向
	VECTOR dir = AsoUtility::VECTOR_ZERO; // 移動方向

	// ダッシュボタン
	bool isDash = false;

	// ゲームパッドが接続数で処理を分ける
	if (GetJoypadNum() == 0)
	{
		// WASDで移動する
		if (ins.IsNew(KEY_INPUT_W)) { dir = AsoUtility::DIR_F; }
		if (ins.IsNew(KEY_INPUT_A)) { dir = AsoUtility::DIR_L; }
		if (ins.IsNew(KEY_INPUT_S)) { dir = AsoUtility::DIR_B; }
		if (ins.IsNew(KEY_INPUT_D)) { dir = AsoUtility::DIR_R; }
		// 右Shiftでダッシュ
		if (ins.IsNew(KEY_INPUT_LSHIFT)) { isDash = true; }
	}
	else
	{
		// ゲームパッド操作
		// 接続されているゲームパッド１の情報を取得
		InputManager::JOYPAD_IN_STATE padState =
			ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
		// アナログキーの入力値から方向を取得
		dir = ins.GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);

		// Rでダッシュ
		if (ins.IsPadBtnNew(
			InputManager::JOYPAD_NO::PAD1,
			InputManager::JOYPAD_BTN::R_TRIGGER)) {
			isDash = true;
		}
	}

	if (!AsoUtility::EqualsVZero(dir))
	{
		// カメラ角度を取得
		Quaternion camRot = scnMng_.GetCamera()->GetQuaRot();
		// カメラの前方向をベクトルとして取り出す
		VECTOR camForward = Quaternion::PosAxis(camRot, AsoUtility::DIR_F);
		// カメラの右方向をベクトルとして取り出す
		VECTOR camRight = Quaternion::PosAxis(camRot, AsoUtility::DIR_R);

		// キャラの向く方向をカメラの前方に固定
		faceDir_ = camForward;

		// dirに合わせて移動ベクトルを合成
		VECTOR moveVec = AsoUtility::VECTOR_ZERO;
		moveVec = VAdd(moveVec, VScale(camForward, dir.z));
		moveVec = VAdd(moveVec, VScale(camRight, dir.x));

		// 移動ベクトルの正規化
		if (AsoUtility::SqrMagnitudeF(moveVec) > 0.0001f)
		{
			moveDir_ = VNorm(moveVec);
		}

		// 回復中は移動速度が半減
		float speed = isHealing_ ? SPEED_MOVE_HEALING : SPEED_MOVE;
		// 移動速度を反映
		movePow_ = VScale(moveDir_, speed);
	}
	else
	{
		//// 静止状態でもカメラの前方向をキャラの前方向にする
		//Quaternion cameraRot = scnMng_.GetCamera()->GetQuaRot();
		//VECTOR camForward = Quaternion::PosAxis(cameraRot, AsoUtility::DIR_F);
		//float dotF = VDot(camForward, upDir);
		//faceDir_ = VNorm(VSub(camForward, VScale(upDir, dotF)));

		// 静止状態でもカメラの前方向をキャラの前方向にする
		VECTOR camForward = scnMng_.GetCamera()->GetForward();
		faceDir_ = camForward;
	}
}

void Player::UpdateProcess(void)
{
	// 移動処理
	ProcessMove();

	// 衝突判定用の調整
	CollisionReserve();
}

void Player::UpdateProcessPost(void)
{
}

void Player::Draw(void)
{
	// 基底クラスの描画
	CharactorBase::Draw();

	// デバッグ表示
	DrawFormatString(0, 0, GetColor(255, 255, 255),
		"(pPosX:%.1f pPosY:%.1f pPosZ:%.1f)",
		transform_.pos.x,
		transform_.pos.y,
		transform_.pos.z);
}

// 衝突判定用の調整
void Player::CollisionReserve(void)
{
	// 線分調整
	if (ownColliders_.count(static_cast<int>(COLLIDER_TYPE::GROUND_LINE)) != 0)
	{
		ColliderLine* colLine = dynamic_cast<ColliderLine*>(
			ownColliders_.at(static_cast<int>(COLLIDER_TYPE::GROUND_LINE)));
		colLine->SetLocalPosStart(COL_LINE_START_LOCAL_POS);
		colLine->SetLocalPosEnd(COL_LINE_END_LOCAL_POS);
	}

	// カプセル調整
	if (ownColliders_.count(static_cast<int>(COLLIDER_TYPE::CAPSULE)) != 0)
	{
		ColliderCapsule* colCapsule = dynamic_cast<ColliderCapsule*>(
			ownColliders_.at(static_cast<int>(COLLIDER_TYPE::CAPSULE)));

		colCapsule->SetLocalPosTop(COL_CAPSULE_TOP_LOCAL_POS);
		colCapsule->SetLocalPosDown(COL_CAPSULE_DOWN_LOCAL_POS);
	}
	
}

void Player::InitLoad(void)
{
	// 基底クラスのリソースロード
	CharactorBase::InitLoad();

	// モデル読み込み
	transform_.SetModel(resMng_.Load(			// 1個 = Load()  複数 = Depulicate()
		ResourceManager::SRC::PLAYER).handleId_);
}

void Player::InitTransform(void)
{
	// 大きさ
	transform_.scl = AsoUtility::VECTOR_ONE;
	
	transform_.quaRot = Quaternion::Identity();
	// Y軸を180度
	transform_.quaRotLocal = Quaternion::AngleAxis(AsoUtility::Deg2RadF(180.0f), AsoUtility::AXIS_Y);

	// 座標
	transform_.pos = VAdd(AsoUtility::VECTOR_ZERO, VScale(AsoUtility::DIR_U, 2600.0f));//64.0f));

	transform_.Update();

}

void Player::InitCollider(void)
{
	// 主に地面との衝突で使用する線分コライダ
	ColliderLine* colLine = new ColliderLine(
		ColliderBase::TAG::PLAYER, &transform_,
		COL_LINE_START_LOCAL_POS, COL_LINE_END_LOCAL_POS);

	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::GROUND_LINE), colLine);

	// 主に壁や木などの衝突で使用するカプセルコライダ
	ColliderCapsule* colCapsule = new ColliderCapsule(
		ColliderBase::TAG::PLAYER, &transform_,
		COL_CAPSULE_TOP_LOCAL_POS, COL_CAPSULE_DOWN_LOCAL_POS, COL_CAPSULE_RADIUS);

	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::CAPSULE), colCapsule);
}

void Player::InitAnimation(void)
{
	// アニメーション
	animController_ = new AnimationController(transform_.modelId);
	animController_->Add(static_cast<int>(ANIM_TYPE::IDLE), 20.0f, resMng_.Load(ResourceManager::SRC::IDLE).path_);

	animController_->Add(static_cast<int>(ANIM_TYPE::RUN), 20.0f, resMng_.Load(ResourceManager::SRC::RUN).path_);

	animController_->Add(static_cast<int>(ANIM_TYPE::FAST_RUN), 20.0f, resMng_.Load(ResourceManager::SRC::FAST_RUN).path_);

	animController_->Add(static_cast<int>(ANIM_TYPE::JUMP), 20.0f, resMng_.Load(ResourceManager::SRC::JUMP_RISING).path_);
}

void Player::InitPost(void)
{
	transform_.Update();

	animController_->Play(0, true);
}

