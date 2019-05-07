#pragma once
#include "gameNode.h"
#include "buccanary.h"
#include "player.h"
#include "itemManager.h"
class secondScene : public gameNode
{
private:
	image* _image;
	POINT _point[2];
	RECT _rc[2];
	player* _player;
	RECT _portal;
	buccanary* _buccanary;
	itemManager* _itemManager;
	bool _showItem;
	vector<string> _sVec[2];
public:
	HRESULT init(player* player);
	void release(void);
	void update(void);
	void render(void);
	void shopWindow(void);
	buccanary* getNPC(void) { return _buccanary; }
	RECT getRect(void) { return _portal; }
	void showItem(void);
	void showText(void);
	secondScene(){}
	~secondScene(){}
};
