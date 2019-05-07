#pragma once
#include "gameNode.h"
#include "enemy.h"

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);

	void removeMinion(int arrNum);

	vector<enemy*> getMinions(void) { return _vMinion; }

	enemyManager() {}
	~enemyManager() {}
};

