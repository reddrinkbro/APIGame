#pragma once
#include "gameNode.h"

class secondScene : public gameNode
{
private:

	//������ ����
	//x
	int _offsetX;
	//y
	int _offsetY;
	//������ ����� �̵��ӵ�(x)
	int _bgSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	secondScene(){}
	~secondScene(){}
};

