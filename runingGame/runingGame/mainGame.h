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
	//�����ӷ���
	int _count;				//������ ���� ī��Ʈ
	int _index;				//������ �̹��� �ε���
	player _player;
	RECT field;
	int _jumpCount;
	int _score;
	int _offsetX;
	int _offsetY;
	//������ ����� �̵��ӵ�(x)
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

