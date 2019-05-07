#pragma once
#include "gameNode.h"
#include "rocket.h"
#include "enemyManager.h"
#include "effect.h"
#include "startScene.h"
#include "secondScene.h"
#include "gameEndScene.h"
#include "objectWind.h"
class mainGame : public gameNode
{
private:
	rocket* _rocket;
	enemyManager* _em;

	enemyEffect* _enemyEffect;
	enemyEnegyBallEffect* _enemyEnegyBallEffect;
	bossHitEffect* _bossHitEffect;
	bossDieEffect* _bossDieEffect;
	playerEffect* _playerEffect;

	objectWind* _objectWind;

	gameNode* _currentScean;
	startScene* _startScene;
	secondScene* _secondScene;
	gameEndScene* _gameEndScene;
	int _sceanNum;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void collision(void);
	virtual void enemyMissileDirection(void);
	virtual void showBoss(void);
	mainGame() {}
	~mainGame() {}
};

