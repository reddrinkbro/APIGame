#pragma once
#include "gameNode.h"
#include "itemManager.h"

enum potion
{
	hp, speed, atk
};
class itemWindow : public gameNode
{
private:
	image* _image;
	float _x, _y;
	RECT _rc;
	float _itemPointX[3], _itemPointY[3];
	
	bool _showInventory;
	int _openCloseinventoryCount;
	itemManager* _itemManager;
	vector <hpPotion*> _vHpItem;
	vector<hpPotion*>::iterator _viHpItem;
	vector <speedPotion*> _vSItem;
	vector<speedPotion*>::iterator _viSItem;
	vector <sword*> _vSword;
	vector<sword*>::iterator _viSword;
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
	void pushItem(int num);
	
	vector <hpPotion*> gethpVec(void) { return _vHpItem; }
	vector <speedPotion*> getSVec(void) { return _vSItem; }
	vector <sword*> getSwordVec(void) { return _vSword; }
	itemWindow(){}
	~itemWindow(){}
};

