#pragma once
#include "gameNode.h"
#include "bullets.h"
class enemyHelicopter : public gameNode
{
	image* _boatImage;
	helicopterBullet* _helicopterBullet;
	RECT _rc;
	float _x, _y;
public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	RECT getRect(void) { return _rc; }
	helicopterBullet* getMissile(void) { return _helicopterBullet; }
	enemyHelicopter(){}
	~enemyHelicopter(){}
};

