#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:
	RECT moveRect;
	RECT circleRect;
	bool isRight;
	bool isUp;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {}
};

