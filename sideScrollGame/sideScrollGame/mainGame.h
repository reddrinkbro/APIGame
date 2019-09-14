#pragma once
#include "gameNode.h"

enum DIRECTION
{
	UP,
	DOWN,
	CENTER
};
struct player1_Skill
{
	RECT _skillRect[12];
	bool isUsing;
};
class mainGame : public gameNode
{
private:
	RECT _player[2]; //플레이어
	RECT _bullet[2]; //총알
	vector<RECT> _playerBullet1;
	vector<RECT> _playerBullet2;
	RECT _playerHealth[2]; //체력
	bool isBulletActive[2];
	bool isBulletMove[2];
	RECT rcTemp;
	int direct;
	int _skill[3];
	player1_Skill skill1;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void player2_skill(void);
	mainGame() {}
	~mainGame() {}
};

