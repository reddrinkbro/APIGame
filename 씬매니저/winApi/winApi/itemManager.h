#pragma once
#include "gameNode.h"
#include "hpPotion.h"
#include "speedPotion.h"
#include "sword.h"
class itemManager : public gameNode
{
private:
	hpPotion* _hpPotion;
	speedPotion* _speedPotion;
	sword* _sword;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	hpPotion* gethpPotion(void) { return _hpPotion; }
	speedPotion* getSpeedPotion(void) { return _speedPotion; }
	sword* getSword(void) { return _sword; }
	itemManager(){}
	~itemManager(){}
};

