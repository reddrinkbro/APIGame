#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:
	RECT player; //플레이어가 움직이는 사각형
	RECT bullet; //총알
	RECT object; //오브젝트
	vector <RECT> bulletVec;
	vector <RECT> objectVec;
	RECT rcTemp;
	RECT playerHp;
	int time; //타이머변수
	int count; //타이머 카운트 변수
	int score;//점수
	int objectIndex; //오브젝트의 인덱스 값
	bool isBulletActive; //총알이 움직이게 하려는지
	bool isBulletMove; // 총알이 움직이는지
	bool isObjectMove[16];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {}
};

