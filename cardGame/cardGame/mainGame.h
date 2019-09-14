#pragma once
#include "gameNode.h"
struct tagCard
{
	RECT rc;
	int num;
	bool isCorrect;
	bool isClick;
	bool isLook;
};


class mainGame : public gameNode
{
private:
	
	tagCard _card[16];
	int cardMix[16];
	int temp;
	bool isCheck;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {}
};

