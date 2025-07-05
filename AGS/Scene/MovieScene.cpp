#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/InputManager.h"
#include "Tutorial.h"
#include "../Manager/Application.h"
#include "MovieScene.h"

MovieScene::MovieScene(void)
{
}

MovieScene::~MovieScene(void)
{
}

void MovieScene::Init(void)
{
    movieHandle_ = LoadGraph("Data/Sound/movie.mp4");
    PlayMovieToGraph(movieHandle_);

    spaceKeyImg_ = LoadGraph( "Data/Image/spaceKey.png" );

    playTime_ = 0.0f;  // 再生経過時間初期化
    isSkipped_ = false;

    // 初期マウス座標を保存
    GetMousePoint(&prevMouseX_, &prevMouseY_);
}

void MovieScene::Update(void)
{
    // シーンスキップの準備
    ReadySkip();
    // シーンスキップ
    SceneSkip();
}

void MovieScene::Draw(void)
{
    // ムービー描画
	DrawGraph(0, 0, movieHandle_, TRUE);

    // スキップ案内
    // まだスキップされていなく、スキップの意思を感じたら
    if (!isSkipped_ && isReadySkip_ && playTime_ <= 5.8)
    {
        SetFontSize(19);
        DrawString(1712, 1020, "長押しでスキップ", 0xffffff);
        DrawRotaGraph(1684, 1030, 0.14f, 0, spaceKeyImg_, true);
    }
}

void MovieScene::Release(void)
{
	DeleteGraph(movieHandle_);
    DeleteGraph(spaceKeyImg_);
}

// シーンスキップの準備
void MovieScene::ReadySkip()
{
    // マウス座標更新
    GetMousePoint(&mouseX_, &mouseY_);

    float dx = static_cast<float>(mouseX_ - prevMouseX_);
    float dy = static_cast<float>(mouseY_ - prevMouseY_);
    float distance = sqrtf(dx * dx + dy * dy);

    // 動いたかどうかを判定（前のフレームと比較）
    if (distance >= 10.0f || InputManager::GetInstance().IsAnyKeyDown() 
        || InputManager::GetInstance().IsTrgMouseLeft())
    {
        isReadySkip_ = true;
    }

    // 長押し判定開始
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        if (!isHolding_) {
            isHolding_ = true;
            holdTime_ = 0.0f;  // 初回だけリセット
        }

        holdTime_ += SceneManager::GetInstance()->GetDeltaTime();
    }
    else 
    {
        isHolding_ = false;
        holdTime_ = 0.0f;
    }

    // 次フレーム用に保存
    prevMouseX_ = mouseX_;
    prevMouseY_ = mouseY_;
}

// シーンのスキップ
void MovieScene::SceneSkip()
{
    playTime_ += SceneManager::GetInstance()->GetDeltaTime();

    if (playTime_ >= MOVIE_LENGTH || holdTime_ >= 1.0f
        && !isSkipped_)
    {
        // 動画終了とみなしてシーン遷移
        SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);
        SoundManager::GetInstance()->PlayOpen();

        isSkipped_ = true;
    }
}
