#pragma once
#include "gameNode.h"
#include "startScene.h"
#include "secondScene.h"
#include "player.h"
#include "saveLoadTest.h"
#include "itemManager.h"
#include "option.h"
class mainGame : public gameNode
{
private:
	option* _option;
	saveLoadTest* _slt;
	startScene* _startScene;
	secondScene* _secondScene;
	gameNode* _gameNode;
	player* _player;
	vector<string> _mLoad;
	bool _save;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void sceneMove(void);
	virtual void selectMap(void);
	virtual void save(void);
	virtual void mapLight(void);
	mainGame() {}
	~mainGame() {}
};

