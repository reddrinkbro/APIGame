#pragma once
#include "gameNode.h"
#include "rocket.h"
#include "enemyManager.h"
#include "effect.h"
#include "animationTest.h"
#include "saveLoadTest.h"

class mainGame : public gameNode
{
private:
	rocket* _rocket;
	enemyManager* _em;
	animationTest* _at;
	missileEffect* _missileEffect;
	beamEffect* _beamEffect;
	saveLoadTest* _slt;

	float _x, _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void collision(void);

	mainGame() {}
	~mainGame() {}
};

