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
	RECT _rc[8];					//�δ��� �簢�� 8��
	int _index;						//�δ����� �ε��� ����
	int _count;						//Ÿ�̸� ī��Ʈ
	int _time;						//Ÿ�̸� �����ð� ����

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

