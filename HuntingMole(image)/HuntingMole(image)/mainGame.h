#pragma once
#include "gameNode.h"

enum CURRENTRECT
{
	CURRENTRECT_0,
	CURRENTRECT_1,
	CURRENTRECT_2,
	CURRENTRECT_3,
	CURRENTRECT_4,
	CURRENTRECT_5,
	CURRENTRECT_6,
	CURRENTRECT_7,
	CURRENTRECT_NULL
};

class mainGame : public gameNode
{
private:
	image* _hammer;
	image* _catch;
	image* _mole;
	image* _tunnul;

	CURRENTRECT _currentRect;
	RECT _rc[8];					//두더지 사각형 8개
	int _index;						//두더지가 인덱스 변수
	int _count;						//타이머 카운트
	int _time;						//타이머 랜덤시간 변수

	bool _isSelected;
	bool _isOnceCheck;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {}
};

