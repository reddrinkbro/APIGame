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
	float* _x;
	float* _y;
	float _currentHp;
	float _maxHp;
	float _def;
	int _money;
	float _speed;
	bool _isShowProgressBar;
public:
	int getMoney(void) { return _money; }
	void setMoney(int money) { _money = money; }
	float getCurrentHp(void) { return _currentHp; }
	HRESULT init(float* x, float* y);
	void release(void);
	void update(void);
	void render(void);
	RECT getRect(void) { return _rc; }
	itemWindow* getItemWindow(void) { return _itemWindow; }
	void save(bool save);
	void showProgressBar(float guage);
	player(){}
	~player(){}
};

