#pragma once
#include "gameNode.h"
class option : public gameNode
{
private:
	image* _image;
	RECT _rc[2];
	float _x, _y;
	int _show;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	RECT getLeft(void) { return _rc[0]; }
	RECT getRight(void) { return _rc[1]; }
	option(){}
	~option(){}
};

