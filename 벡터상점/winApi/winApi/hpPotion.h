#pragma once
#include "gameNode.h"
class hpPotion : public gameNode
{
private:
	image* _image;
	RECT _rc;
	float* _rcX;
	float* _rcY;
	int _cost;
	float _recovery;
public:
	float* getX(void) { return _rcX; }
	float* getY(void) { return _rcY; }
	void setX(float* rcX) { _rcX = rcX; }
	void setY(float* rcY) { _rcY = rcY; }
	int getCost(void) { return _cost; }
	float getRecovery(void) { return _recovery; }
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void setPotion(float* rcX, float* rcY);
	RECT getRect(void) { return _rc; }
	hpPotion(){}
	~hpPotion(){}
};

