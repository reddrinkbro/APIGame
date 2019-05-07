#pragma once
#include "gameNode.h"
#include "itemManager.h"

enum potion
{
	hp, speed
};
class itemWindow : public gameNode
{
private:
	image* _image;
	float _x, _y;
	RECT _rc;
	float _itemPointX[2], _itemPointY[2];
	POINT _point[2];
	bool _showInventory;
	int _openCloseinventoryCount;
	itemManager* _itemManager;
	vector <hpPotion*> _vHpItem;
	vector<hpPotion*>::iterator _viHpItem;
	vector <speedPotion*> _vSItem;
	vector<speedPotion*>::iterator _viSItem;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	bool getShowInventory(void) { return _showInventory; }
	void setShowInventory(bool showInventory , int openCloseinventoryCount) {
		_showInventory = showInventory;
		_openCloseinventoryCount = openCloseinventoryCount;
	}
	void usingItem(int num);
	void showInventory(void);
	void pushPotion(int num);
	vector <hpPotion*> gethpVec(void) { return _vHpItem; }
	vector <speedPotion*> getSVec(void) { return _vSItem; }
	itemWindow(){}
	~itemWindow(){}
};

