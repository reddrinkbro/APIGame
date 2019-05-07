#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "enemyBoss.h"
class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;
	enemyBoss* _enemyBoss;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void addMinion(void);
	void removeMinion(int arrNum);
	void appearBoss(void);
	vector<enemy*> getMinions(void) { return _vMinion; }
	enemyBoss* getBoss(void) { return _enemyBoss; }

	enemyManager() {}
	~enemyManager() {}
};

