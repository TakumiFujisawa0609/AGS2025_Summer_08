#pragma once
class AimButton
{
public:

	//ボタンの状態
	enum BUTTON_STATE
	{
		OFF,//通常
		ON,//クリック可能


		MAX,//最大
	};

	AimButton(int posX, int posY, int sizeW, int sizsH);
	~AimButton();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//ボタンの状態を返す
	BUTTON_STATE GetButtonState();
	void SetButtonOn(void) { buttonState_ = BUTTON_STATE::ON; }
	void SetButtonOff(void) { buttonState_ = BUTTON_STATE::OFF; }

	//ボタンの状態をセット
	void ButtonStateOn(void);

	bool GetNowClick(void) { return nowClick_; }
	
	int GetSensi(void) { return sensi_; }
	void SetSensi(int sensi) { sensi_ = sensi; }

private:

	BUTTON_STATE buttonState_;//ボタン状態
	//ボタン画像ハンドル
	int handle_[MAX];

	int posX_; //X座標
	int posY_; //Y座標

	int sizeW_; //横幅
	int sizeH_; //縦幅

	bool prevMouseDown_ = false;

	// 今押された
	bool nowClick_;

	// 戦士
	int sensi_;

};

