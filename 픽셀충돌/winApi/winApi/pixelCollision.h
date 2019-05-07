#pragma once
#include "gameNode.h"
#include "playerTank.h"
#include "effect.h"
class pixelCollision : public gameNode
{
private:
	playerTank* _playerTank;
	missileEffect* _effect;
	//픽셀 충돌 탐지할 y값 센서

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void collision(void);
	void pixel(void);
	pixelCollision() {}
	~pixelCollision() {}
};

