#pragma once
#include "gameNode.h"

#define PI 3.141592654f
#define ENEMYMAX 5

struct player
{
	RECT rc;
	float bulletAngle;
	float time;
	float gravity;
	bool isJump;
};
class mainGame : public gameNode
{
private:
	RECT _enemy;
	vector<RECT> _enemyVec;
	//프레임렌더
	int _count;				//프레임 돌릴 카운트
	int _index;				//프레임 이미지 인덱스
	player _player;
	RECT field;
	int _jumpCount;
	int _score;
	int _offsetX;
	int _offsetY;
	//루프될 배경의 이동속도(x)
	int _bgSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
	void jump(void);
	void intersect(void);
	void enemyCreate(void);
	void doubleJump(void);
	mainGame() {}
	~mainGame() {}
};

