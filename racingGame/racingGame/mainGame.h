#pragma once
#include "gameNode.h"

#define PI 3.141592654f
#define ENEMYMAX 7

struct arrow
{
	POINT start;
	POINT end;
	int radius;			
	int length;			
	float angle;		
};

class mainGame : public gameNode
{
private:
	RECT _enemy;
	vector<RECT> _enemyVec;
	//�����ӷ���
	RECT _player;
	arrow _arrow;
	RECT rc;
	int _score;
	int _offsetX;
	int _offsetY;
	//������ ����� �̵��ӵ�(x)
	int _bgSpeed;
	float _speed;
	bool isSpeedDown;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
	void enemyCreate(void);
	mainGame() {}
	~mainGame() {}
};

