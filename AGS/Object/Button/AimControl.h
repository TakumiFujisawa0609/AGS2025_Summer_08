#pragma once
#include <vector>

class AimButton;

class AimControl
{

public:
	//　定数
	static constexpr int BUTTON_NUM = 5;

	static constexpr float SENSI_MAX = 0.00055f;
	static constexpr float SENSI_HIGH = 0.00045f;
	static constexpr float SENSI_CENTER = 0.00035f;//デフォルトの感度
	static constexpr float SENSI_ROW = 0.00025f;
	static constexpr float SENSI_MIN = 0.00015f;

public:
	AimControl(void);
	~AimControl(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//ブロックアクションのgameSceneを参照する
	void ButtonON(void);

	int GetButtonSensi(void);

	float GetcontrolSensi_(void);
	void  SetcontrolSensi_(float controlSensi) { controlSensi_ = controlSensi; }
private:

	std::vector<AimButton*> aimButtons_;


	
	int sensi_;
	int pastSesi;
};


