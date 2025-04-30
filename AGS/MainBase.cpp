#include <DxLib.h>


//変数宣言
 

//カメラ----------------------------------------------------

//カメラ位置
VECTOR cameraPos;

// ステージ----------------------------------------------------


//ステージ拡大サイズ設定
VECTOR stageScalePos;
//ステージ位置
VECTOR stagePos;

//２つ目ステージ拡大サイズ設定
VECTOR stage2ScalePos;
//２つ目ステージ位置
VECTOR stage2Pos;

//ステージの配置座標（ｚ）
float stageLoopPosZ;
//一つ目のステージ位置を変更する場合、true
bool isLoopStage;


//一つ目のステージモデルのロード
int stageModeId;
//2つ目ステージモデルのロード
int stage2ModeId;

//弾丸----------------------------------------------------
constexpr float SHOT_MOVE_POW_Z = 80.0f;

// プレイヤーの弾の生存距離
constexpr float PLAYER_SHOT_ALIVE_POS_Z = 6000.0f;

// プレイヤーの弾情報
int playerShotModelId;
VECTOR playerShotPos ;
// プレイヤーの弾の生存判定
bool isAlivePlayerShot ;


// WinMain関数
//---------------------------------
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	// ウィンドウサイズ
	SetGraphMode(1000, 800, 32);
	ChangeWindowMode(true);
	// DxLibの初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	void Init(void);
	void Update(void);
	void Draw(void);
	void Relese(void);




	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Init();
		Update();
		Draw();

		ScreenFlip();
	}
	// DxLibの後始末
	if (DxLib_End() == -1)
	{
		return -1;
	}
	return 0;
}

void Init(void)
{
	//カメラ
	cameraPos = VGet(0.0f, 150.0f, -500.0f);



	stageScalePos = VGet(10.0f, 10.0f, 10.0f);
	//ステージ位置
	stagePos = VGet(0.0f, -50.0f, 0.0f);


	//２つ目ステージ拡大サイズ設定
	stage2ScalePos = VGet(10.0f, 10.0f, 10.0f);
	//２つ目ステージ位置
	stage2Pos = VGet(0.0f, -50.0f, 8000.0f);

	stageLoopPosZ = 8000.0f;

	isLoopStage = true;

	//一つ目のステージモデルのロード
	stageModeId = MV1LoadModel("Model/Stage.mv1");
	//2つ目ステージモデルのロード
	stage2ModeId = MV1LoadModel("Model/Stage.mv1");



	//ステージの拡大
	MV1SetScale(stageModeId, stageScalePos);
	//ステージ位置
	MV1SetPosition(stageModeId, stagePos);

	//ステージ2の拡大
	MV1SetScale(stage2ModeId, stage2ScalePos);
	//ステージ位置
	MV1SetPosition(stage2ModeId, stage2Pos);


	// プレイヤーの弾情報
	playerShotModelId = -1;
	playerShotPos = VGet(0.0f, 0.0f, 0.0f);
	// プレイヤーの弾の生存判定
	isAlivePlayerShot = false;
}

void Update(void)
{
	//ステージループ
	if (cameraPos.z > stageLoopPosZ)
	{

		//座標を奥に移動
		stageLoopPosZ += 8000.0f;
		if (isLoopStage)
		{
			//一つ目のステージ位置変更
			MV1SetPosition(stageModeId, stagePos = VGet(stagePos.x, stagePos.y, stageLoopPosZ));
			isLoopStage = false;
		}
		else
		{
			//二つ目のステージ位置変更
			MV1SetPosition(stage2ModeId, stage2Pos = VGet(stage2Pos.x, stage2Pos.y, stageLoopPosZ));
			isLoopStage = true;

		}
	}



	if (CheckHitKey(KEY_INPUT_SPACE) == true)
	{
	}
}

void Draw(void)
{
	// 描画スクリーンの設定
	SetDrawScreen(DX_SCREEN_BACK);
	// 描画スクリーンを初期化
	ClearDrawScreen();


	//カメラ設定
	 //setDrawScreenの後、描画処理の前にカメラを設定
	SetCameraPositionAndAngle(VGet(cameraPos.x,cameraPos.y,cameraPos.z), 0, 0, 0);


	////仮表示
	//VECTOR spherePos = VGet(0.0f, 20.0f, 0.0f);
	//DrawSphere3D(spherePos, 300.0f, 30, 0xff0000, 0xff0000, true);




	// 描画処理

	//ステージの描画
	MV1DrawModel(stageModeId);
	MV1DrawModel(stage2ModeId);

	DrawFormatString(0, 100, 0xfffff, "座標 :(% .2f, % .2f, % .2f)", cameraPos.x, cameraPos.y, cameraPos.z, true);

}
void Relese(void)
{
}