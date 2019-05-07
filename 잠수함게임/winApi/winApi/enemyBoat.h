#pragma once
#include "gameNode.h"
#include "bullets.h"
class enemyBoat : public gameNode
{
private:
	image* _boatImage;
	boatBullet* _boatBullet;
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
	boatBullet* getMissile(void) { return _boatBullet; }
	enemyBoat(){}
	~enemyBoat(){}
};

