#include <DxLib.h>
#include "ItemVaccine.h"

ItemVaccine::ItemVaccine(void)
{
}

ItemVaccine::~ItemVaccine(void)
{
}

void ItemVaccine::Draw()
{
    // ワクチンが拾われてなかったら描画
    if (!isPickUpV_) MV1DrawModel(modelId_);

    // 最初のワクチン取得時に
    if (vNumber_ == 2)
    {
        // 今の時間を保存
        int now = GetNowCount();
        if (now - pickUpTime_ <= SHOW_DURATION)
        {
            // 拾ってから3秒以内なら画像表示
            DrawRotaGraph(955, 540, 0.5, 0, vImage_, true);
        }
    }
}

void ItemVaccine::SetParam()
{

	scale_ = DEFAULT_VACCINE_SCALE;
}


void ItemVaccine::SetApplyEffect()
{
}


