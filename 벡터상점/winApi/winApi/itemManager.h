#pragma once
#include "gameNode.h"
#include "hpPotion.h"
#include "speedPotion.h"
class itemManager : public gameNode
{
private:
	hpPotion* _hpPotion;
	speedPotion* _speedPotion;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	hpPotion* gethpPotion(void) { return _hpPotion; }
	speedPotion* getSpeedPotion(void) { return _speedPotion; }
	itemManager(){}
	~itemManager(){}
};

