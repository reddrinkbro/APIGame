#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "bullets.h"

class rocket;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

	bullet* _bullet;
	rocket* _rocket;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void setMinion(void);
	void removeMinion(int arrNum);
	void minionBulletFire(void);
	void collision(void);

	bullet* getBullet(void) { return _bullet; }

	vector<enemy*> getMinions(void) { return _vMinion; }

	void setRocketMemoryAddress(rocket* rk) { _rocket = rk; }

	enemyManager() {}
	~enemyManager() {}
};

