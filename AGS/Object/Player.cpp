#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Manager/Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Utility/AsoUtility.h"
#include "../Object/Player.h"

void Player::Init(void)
{
	movedPos_ = { 0.0f, 0.0f, 0.0f };
	pos_ = { 0.0f, 0.0f, 0.0f };
	MV1SetPosition(modelId_, pos_);

	// ˆÚ“®ƒxƒNƒgƒ‹‰Šú‰»
	moveVec_ = AsoUtility::VECTOR_ZERO;

	// ƒ‚ƒfƒ‹‚ÌŠp“xİ’è
	rot_ = { 0.0f, 0.0f, 0.0f };
	// ƒ‚ƒfƒ‹‚ÌŠp“x
	localRot_ = INIT_MODEL_ROT_OFFSET;

	// ƒJƒƒ‰ƒAƒ“ƒOƒ‹
	cameraAngle_ = { 0.0f, 0.0f, 0.0f };

	// ‘Ì—Í‰Šú‰»
	hp_ = DEFAULT_HP;

	// ‰ñ•œ‰Â”\”
	heal_ = 0;
	isHeal_ = false;

	isStop_ = false;

<<<<<<< HEAD
	isAlive_ = true;
=======
	damegeHandle_ = LoadGraph("Data/Image/Effect/Damege.png");
	defoHandle_ = LoadGraph("Data/Image/Effect/Damege_01.png");

>>>>>>> origin/ando_Ui
}

void Player::Update(VECTOR angle)
{
	// ƒJƒƒ‰ƒAƒ“ƒOƒ‹æ“¾
	cameraAngle_ = angle;

	// ˆÚ“®ˆ—
	ProcessMove(cameraAngle_);
	//SetRotation();

	// HP
	Hp();

	// ƒ_ƒ[ƒW•\Œ»
	DamageEffect();


	if (CheckHitKey(KEY_INPUT_0)) { isAlive_ = false; }
}

void Player::Draw(void)
{
	//VECTOR startPos = VAdd(playerPos_, VGet(0.0f, 30.0f, 0));                          // “G‚ÌÀ•W
	//VECTOR endPos = VAdd(playerPos_, VGet(0.0f, 160.0f, 0));  // ƒJƒvƒZƒ‹‚Ìã’[i‚‚³60‚Ì—áj
	//float radius = 45.0f;	// ”¼Œa45i’²®‰Âj

	//VECTOR centerPos = VAdd(pos_, VGet(0.0f, 110, 0));

	//DrawSphere3D(centerPos, radius, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);	// ‹…‚ğ•`‰æ

	// ƒvƒŒƒCƒ„[À•W
	DrawFormatString(0, 40, 0xffffff, "playerPos:(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);

	//DrawFormatString(0, 700, 0xffffff, "isStop_P:%d", isStop_);
	//DrawFormatString(0, 740, 0xffffff, "isAlive_P:%d", isAlive_);
	//
	//DrawFormatString(500, 0, 0xffffff, "%d", hp_);

	if (redEffectAlpha_ > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, redEffectAlpha_);

		int thickness = 50; // Ô‚¢‰‚Ì‘¾‚³i’²®‰Âj
		int screenW = 1920;
		int screenH = 1080;

		int red = GetColor(255, 0, 0);

		// ã
		DrawBox(0, 0, screenW, thickness, red, TRUE);
		// ‰º
		DrawBox(0, screenH - thickness, screenW, screenH, red, TRUE);
		// ¶
		DrawBox(0, thickness, thickness, screenH - thickness, red, TRUE);
		// ‰E
		DrawBox(screenW - thickness, thickness, screenW, screenH - thickness, red, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

<<<<<<< HEAD
=======
	if (hp_ == 1)
	{
		DrawGraph(0, 0, defoHandle_, true);

		// alphaå€¤è¨ˆç®—
		int alpha = (int)(((sin(count * 0.05) * 0.5) + 0.5) * 255+30); // 0ã€œ255
		SoundManager::GetInstance()->PlayDamage();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(0, 0, damegeHandle_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		count= count+1; // æ¯ãƒ•ãƒ¬ãƒ¼ãƒ å¢—ã‚„ã™
	}
	else
	{
		SoundManager::GetInstance()->StopDamege();
	}
>>>>>>> origin/ando_Ui
}

void Player::Release(void)
{
<<<<<<< HEAD
=======
	DeleteGraph(damegeHandle_);
	DeleteGraph(defoHandle_);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
>>>>>>> origin/ando_Ui
}

// HP
void Player::Hp(void)
{
	static float holdTime = 0.0f;
	float deltaTime = SceneManager::GetInstance()->GetDeltaTime();

	// €–Sˆ—
	if (hp_ == 0)
	{
		isStop_ = true;
		isAlive_ = false;

		SoundManager::GetInstance()->StopWalk();
	}

	// HPÅ‘å§ŒÀ
	if (hp_ >= DEFAULT_HP)
		hp_ = DEFAULT_HP;

	// QƒL[‚ğ‰Ÿ‚µ‚½uŠÔ
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_Q) && heal_ > 0 && hp_ < DEFAULT_HP)
	{
		isHoldingQ_ = true;
		holdTime = 0.0f;

		isHeal_ = false;
	}

	// QƒL[‚ğ—£‚µ‚½uŠÔ
	if (InputManager::GetInstance().IsTrgUp(KEY_INPUT_Q))
	{
		isHoldingQ_ = false;
		holdTime = 0.0f;

		SoundManager::GetInstance()->StopHeal();
	}

	// Q‚ğ‰Ÿ‚µ‘±‚¯‚Ä‚¢‚éŠÔ‚ÍŠÔ‚ğ‰ÁZ
	if (isHoldingQ_)
	{
		SoundManager::GetInstance()->PlayHeal();
		holdTime += deltaTime;

		if (holdTime >= 2.0f)
		{
			hp_ += 1;
			heal_ -= 1;

			SoundManager::GetInstance()->PlayHeal();
			SoundManager::GetInstance()->PlayHealVoice();

			isHeal_ = true;

			// ƒŠƒZƒbƒg
			isHoldingQ_ = false;
			holdTime = 0.0f;
		}
	}
}

void Player::ModelReflect()
{
	// i‚ñ‚Å‚æ‚©‚Á‚½‚ç
	if (!isStop_)
	{
		pos_ = movedPos_;
	}

	MV1SetPosition(modelId_, pos_);
}

void Player::Damage(int damage)
{
	// ƒ_ƒ[ƒW‚ğó‚¯‚é
	hp_ -= damage;

	// ‘Ì—Í‚ª0‚É‚È‚Á‚½‚ç0‚ÉŒÅ’è
	if (hp_ <= 0)
	{ 
		hp_ = 0; 
		SoundManager::GetInstance()->PlayDie();
	}
	else if (hp_ == 1)
	{
		SoundManager::GetInstance()->PlayHit();
	}
}

void Player::DamageEffect()
{
	// HP‚ª1‚È‚çÔ“_–Å‰‰o
	if (hp_ == 1)
	{
		// ƒAƒ‹ƒtƒ@’l•Ï‰»
		if (redEffectIncreasing_)
		{
			redEffectAlpha_ += 2; // ‘‚â‚·
			if (redEffectAlpha_ >= 150)
			{
				redEffectAlpha_ = 150;
				redEffectIncreasing_ = false;
			}
		}
		else
		{
			redEffectAlpha_ -= 2; // Œ¸‚ç‚·
			if (redEffectAlpha_ <= 0)
			{
				redEffectAlpha_ = 0;
				redEffectIncreasing_ = true;
			}
		}
	}
	else
	{
		// HP‚ª1ˆÈŠO‚È‚çÁ‚·
		redEffectAlpha_ = 0;
	}
}

void Player::SetStop(bool isStop)
{
	isStop_ = isStop;
}

// ‰ñ•œ‰Â”\”
void Player::Heal(int heal)
{
	heal_ += heal;
}
																	
VECTOR Player::GetPPos(void)
{
	return pos_;
}

VECTOR Player::GetMovedPos(void)
{
	return movedPos_;
}

bool Player::GetAlive(void)
{
	return isAlive_;
}

int Player::GetHp()
{
	return hp_;
}

int Player::GetHeal()
{
	return heal_;
}

// ‰ñ“]İ’è
void Player::SetRotation(void)
{
	// ‰ñ“]s—ñ‚ğg—p‚µ‚½Šp“xİ’è
	// ---------------------------
	// ’PˆÊs—ñ‚ğİ’è‚·‚é
	MATRIX mat = MGetIdent();

	// ƒ‚ƒfƒ‹©‘Ì‚ÌY²‰ñ“]s—ñ‚ğì¬‚·‚é
	MATRIX mGetRotY = MGetRotY(rot_.y);

	// ƒ‚ƒfƒ‹‚Ì•â³—pY²‰ñ“]s—ñ‚ğì¬‚·‚é
	MATRIX mGetLocalRotY = MGetRotY(localRot_.y);

	// s—ñ‚ğ‡¬
	mat = MMult(mat, mGetRotY);
	mat = MMult(mat, mGetLocalRotY);

	// s—ñ‚ğg—p‚µ‚Äƒ‚ƒfƒ‹‚ÌŠp“x‚ğİ’è
	MV1SetRotationMatrix(modelId_, mat);
}

// ˆÚ“®ˆ—
void Player::ProcessMove(VECTOR angle)
{
	// ˆÚ“®•ûŒü‚ğŒˆ‚ß‚é
	moveVec_ = AsoUtility::VECTOR_ZERO;
	if (InputManager::GetInstance().IsNew(KEY_INPUT_S)) {
		moveVec_ = VAdd(moveVec_, AsoUtility::DIR_F);
		SoundManager::GetInstance()->PlayWalk();
	}
	if (InputManager::GetInstance().IsNew(KEY_INPUT_W)) { 
		moveVec_ = VAdd(moveVec_, AsoUtility::DIR_B);
		SoundManager::GetInstance()->PlayWalk();
	}
	if (InputManager::GetInstance().IsNew(KEY_INPUT_A)) {
		moveVec_ = VAdd(moveVec_, AsoUtility::DIR_R);
		SoundManager::GetInstance()->PlayWalk();
	}
	if (InputManager::GetInstance().IsNew(KEY_INPUT_D)) { 
		moveVec_ = VAdd(moveVec_, AsoUtility::DIR_L); 
		SoundManager::GetInstance()->PlayWalk();
	}
	if (!CheckHitKey(KEY_INPUT_W) && !CheckHitKey(KEY_INPUT_A) &&
		!CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D)) {
		SoundManager::GetInstance()->StopWalk();
	}

	// ˆÚ“®ˆ—
	// “®‚¢‚Ä‚¢‚½‚ç
	if (!AsoUtility::EqualsVZero(moveVec_))
	{
		// ƒJƒƒ‰Šp“x•ªİ’è‚·‚é
		MATRIX cameraMatY = MGetRotY(angle.y);
		moveVec_ = VTransform(moveVec_, cameraMatY);

		// À•WXV
		moveVec_ = VNorm(moveVec_);

		// Q’·‰Ÿ‚µ’†‚Í”¼•ª‚Ì‘¬“x
		float speed = isHoldingQ_ ? MOVE_SPEED * 0.5f : MOVE_SPEED;
		moveVec_ = VScale(moveVec_, speed);

		// ˆÚ“®—\’èˆÊ’u‚ÉˆÚ“®ˆ—‚ğ‘ã“ü
		movedPos_ = VAdd(pos_, moveVec_); 

		// •ûŒü‚ğŠp“x‚É•ÏŠ·‚·‚é(XZ•½–Ê@Y²)
		moveVecRad_.y = atan2f(moveVec_.x, moveVec_.z);

		// ŒvZŠp“x‚ğİ’è
		rot_.y = moveVecRad_.y;
	}
}



