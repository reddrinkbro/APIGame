#pragma once
#include "gameNode.h"
#include "tankMap.h"

//��ũ 4����
enum TANKDIRECTION
{
	TANKDIRECTION_LEFT,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_UP,
	TANKDIRECTION_DOWN,
};

class tank : public gameNode
{
private:
	tankMap* _tankMap;
	image* _image;
	TANKDIRECTION _direction;
	RECT _rc;
	float _x, _y;
	float _speed;
	int count;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void tankMove(bool isMove);
	void setTankPosition();

	//Ÿ�ϸ� �޸� ��ũ
	void setTankMapMemoryLink(tankMap* tm) { _tankMap = tm; }

	tank() {}
	~tank() {}
};

