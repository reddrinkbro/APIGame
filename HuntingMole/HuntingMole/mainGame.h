#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:
	RECT rc[8];
	int score;
	int randNum;
	int gameSpeed;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {}
};

