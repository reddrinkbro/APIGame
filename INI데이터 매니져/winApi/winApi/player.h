#pragma once
#include "gameNode.h"
#include "animation.h"
#include "progressBar.h"
#include "itemWindow.h"
#include "itemManager.h"

class player : public gameNode
{
private:
	vector<string> _pSaveLoad;
	image* _image;
	animation* _animation;
	progressBar* _progressBar;
	itemWindow* _itemWindow;
	itemManager* _itemManager;
	RECT _rc;
	float _x, _y;
	float _currentHp;
	float _maxHp;
	float _def;
	int _money;
	float _speed;
public:
	int getMoney(void) { return _money; }
	void setMoney(int money) { _money = money; }
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	RECT getRect(void) { return _rc; }
	void characterMapMove(float x, float y);
	itemWindow* getItemWindow(void) { return _itemWindow; }
	void save(bool save);
	
	player(){}
	~player(){}
};

