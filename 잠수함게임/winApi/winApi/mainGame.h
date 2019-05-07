#pragma once
#include "gameNode.h"
#include "rocket.h"
#include "enemyManager.h"
#include "effect.h"
#include "startScene.h"
#include "secondScene.h"
#include "gameEndScene.h"
class mainGame : public gameNode
{
private:
	rocket* _rocket;
	enemyManager* _em;

	enemyEffect* _enemyEffect;
	rocketLauncherEffect* _rocketLauncherEffect;
	missileEffect* _missileEffect;
	helicopterDieEffect* _helicopterDieEffect;
	playerEffect* _playerEffect;

	gameNode* _currentScean;
	startScene* _startScene;
	secondScene* _secondScene;
	gameEndScene* _gameEndScene;
	int _sceanNum;
	RECT rc;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void collision(void);
	virtual void enemyMissileDirection(void);
	mainGame() {}
	~mainGame() {}
};

