#pragma once
class ExitButton
{
public:

	//ボタンの状態
	enum BUTTON_STATE
	{
		DEFOAULT,//通常
		HOVER,//クリック可能
		DISABLED,//クリック不可

		MAX,//最大
	};

	ExitButton(int posX, int posY, int sizeW, int sizsH);
	~ExitButton();



	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//ボタンの状態を返す
	BUTTON_STATE GetButtonState(void);
private:

	BUTTON_STATE buttonState_;//ボタン状態
	//ボタン画像ハンドル
	int handle_[MAX];

	int posX_; //X座標
	int posY_; //Y座標

	int sizeW_; //横幅
	int sizeH_; //縦幅
};

