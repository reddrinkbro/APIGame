#pragma once
#include "gameNode.h"
#define PI 3.141592654f
struct player
{
	RECT rc;
	float bulletAngle;
	float time;
	float gravity;
	bool isJump;
	bool isClimbing;
};
class mainGame : public gameNode
{
private:
	image* _bgImage;
	image* _fieldImage;
	image* _objectImage;
	RECT _rc;

	//프레임렌더
	image* _mario;		//프레임 이미지
	int _count;				//프레임 돌릴 카운트
	int _index;				//프레임 이미지 인덱스
	bool _isLeft;			//왼쪽 체크
	bool _isMove;			//움직이기는가
	player _player;
	RECT field;
	RECT object;
	int finishTime;
	bool _isClimb;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
	void jump(void);
	void jumpAfterRect(void);
	void intersect(void);
	mainGame() {}
	~mainGame() {}
};

