#pragma once
#include "gameNode.h"
#include "rocket.h"
#include "enemyManager.h"
#include "shootingEffect.h"

class shootingScene : public gameNode
{
private:
	rocket* _rocket;
	enemyManager* _em;
	missileEffect* _missileEffect;
	beamEffect* _beamEffect;

	float _x, _y;
	char _text[64];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void collision(void);

	shootingScene() {}
	~shootingScene() {}
};

