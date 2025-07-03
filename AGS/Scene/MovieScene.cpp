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


    playTime_ = 0.0f;  // 再生経過時間初期化
}

void MovieScene::Update(void)
{
    playTime_ += SceneManager::GetInstance()->GetDeltaTime();

    if (playTime_ >= MOVIE_LENGTH || InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE)
        )//  || InputManager::GetInstance().IsTrgMouseLeft())
    {
        // 動画終了とみなしてシーン遷移
        SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);
        SoundManager::GetInstance()->PlayOpen();
    }
}

void MovieScene::Draw(void)
{
	DrawGraph(0, 0, movieHandle_, TRUE);
}

void MovieScene::Release(void)
{
	DeleteGraph(movieHandle_);
}
