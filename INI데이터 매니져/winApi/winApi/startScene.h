#pragma once
#include "gameNode.h"
#include "player.h"
#include "itemManager.h"

class startScene : public gameNode
{
private:
	RECT _rc;
	player* _player;
	itemManager* _itemManager;
	int _renderValue;
public:
	int getRenderValue(void) { return _renderValue; }
	void setRenderValue(int renderValue) { _renderValue = renderValue; }
	HRESULT init(player* player);
	void release(void);
	void update(player* player);
	void render(void);
	RECT getRect(void) { return _rc; }

	startScene(){}
	~startScene(){}
};

