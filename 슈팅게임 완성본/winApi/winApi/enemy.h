#pragma once
#include "gameNode.h"
#include "bullets.h"
class enemy : public gameNode
{
protected:
	image* _image;
	float _x, _y;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	float _rndTimeCount;
	float _worldTimeCount;

	int _randDomDirction;
	enemyBullet* _enemyBullet;
public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	enemyBullet* getMissile(void) { return _enemyBullet; }
	RECT getRect(void) { return _rc; }
	void removeMissile(int arrNum);
	enemy(void);
	~enemy(void){}
};

