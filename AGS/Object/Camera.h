#pragma once
class Player;

class Camera
{

public:
	Camera();
	~Camera();
	void Init(Player* player);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	Player* player_;
	
};

