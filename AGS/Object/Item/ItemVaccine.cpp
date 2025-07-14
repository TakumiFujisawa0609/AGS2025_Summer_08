#include <DxLib.h>
#include "../Camera.h"
#include "../Player.h"
#include "ItemVaccine.h"
#include <corecrt_math.h>

ItemVaccine::ItemVaccine(void)
{
}

ItemVaccine::~ItemVaccine(void)
{
}

void ItemVaccine::Draw()
{
    VECTOR pPos = player_->GetPPos();
    float dis = VSize(VSub(pPos, pos_));

    //// ワクチンが拾われてなかったら描画
    //if (dis < 2400 && state_ != STATE::PICKUP_V)
    //{
    //    MV1DrawModel(modelId_);
    //}


    // カメラ→敵へのベクトルを正規化して toEnemy を定義
    VECTOR toEnemy = VNorm(VSub(pos_, camera_->GetPos()));

    // カメラの前方向ベクトル
    VECTOR cameraForward = camera_->GetForward();

    // 内積で視野内か判定
    const float fovCos = cosf(52.0f * DX_PI_F / 180.0f);

    float dot = VDot(toEnemy, cameraForward);

    // カメラの前方向とある程度一致している（＝視野内）なら描画
    if (dot > fovCos && dis < 2400 && state_ != STATE::PICKUP_V)
    {
        MV1DrawModel(modelId_);
    }

	// スポーン位置の球体を描画
	for (const auto& point : vaccineSpawnPoints)
	{
	//	DrawSphere3D(point.pos, 230, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), false);
	}
}

void ItemVaccine::SetParam()
{
	scale_ = DEFAULT_VACCINE_SCALE;
}

