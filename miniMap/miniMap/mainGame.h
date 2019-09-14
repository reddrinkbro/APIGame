#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:
	image* _bgImage;
	image* _MoveImage;
	RECT _rc;
	RECT _field;
	RECT _mini;
	int _count;
	int _alpha;
	int _count1;
	int _alpha1;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {}
};

