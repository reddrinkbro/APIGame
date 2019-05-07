#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "enemyBoat.h"
#include "enemyHelicopter.h"
class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;
	typedef vector<enemyBoat*> vBoat;
	typedef vector<enemyBoat*>::iterator viBoat;
	typedef vector<enemyHelicopter*> vheli;
	typedef vector<enemyHelicopter*>::iterator viheli;
private:
	vEnemy _vMinion;
	viEnemy _viMinion;
	vBoat _vBoat;
	viBoat _viBoat;
	vheli _vHeli;
	viheli _viHeli;
	enemyBoat* _enemyBoat;
	enemyHelicopter* _enemyHelicopter;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void addMinion(void);
	void removeMinion(int arrNum);
	void removeBoat(int arrNum);
	void removeHeli(int arrNum);
	void positionReset(void);
	vector<enemy*> getMinions(void) { return _vMinion; }
	vector<enemyBoat*> getBoat(void) { return _vBoat; }
	vector<enemyHelicopter*> getHeli(void) { return _vHeli; }
	enemyManager() {}
	~enemyManager() {}
};

