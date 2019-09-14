#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:
	RECT rc[8];
	int fail;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {}
};

