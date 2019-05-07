#pragma once
#include "gameNode.h"
#include "player.h"
#include "itemManager.h"

class secondScene : public gameNode
{
private:
	player* _player;
	itemManager* _itemManager;
	float _x, _y;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void nextScene(void);
	secondScene(){}
	~secondScene(){}
};

