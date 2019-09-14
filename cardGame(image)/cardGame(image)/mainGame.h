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
	bool isClick;
	float _time;
	int _count;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {}
};

