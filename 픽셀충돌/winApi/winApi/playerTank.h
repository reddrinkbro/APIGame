#pragma once
#include "gameNode.h"
#include "tankBullet.h"
class playerTank : public gameNode
{
private:
	image* _image;
	tankBullet* _tankBullet;
	RECT _rc;
	float _tankCenterX, _tankCenterY;
	float _tankEndX, _tankEndY;
	float _angle;
	int _probeY;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	tankBullet* getMissile(void) { return _tankBullet; }
	playerTank(){}
	~playerTank(){}
};

