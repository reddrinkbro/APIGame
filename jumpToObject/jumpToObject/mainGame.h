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

	//�����ӷ���
	image* _mario;		//������ �̹���
	int _count;				//������ ���� ī��Ʈ
	int _index;				//������ �̹��� �ε���
	bool _isLeft;			//���� üũ
	bool _isMove;			//�����̱�°�
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

