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
public:
	HRESULT init(player* player);
	void release(void);
	void update(player* player);
	void render(void);

	RECT getRect(void) { return _rc; }

	startScene(){}
	~startScene(){}
};

