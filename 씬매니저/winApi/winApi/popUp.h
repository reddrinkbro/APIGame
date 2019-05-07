#pragma once
#include "gameNode.h"
class popUp : public gameNode
{
private:
	image* _image;
	RECT _rc[2];
	float _x, _y;
	bool _isShow;
public:
	bool getIsShow(void) { return _isShow; }
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void showPopUp(void);
	RECT getLeft(void) { return _rc[0]; }
	RECT getRight(void) { return _rc[1]; }
	popUp(){}
	~popUp(){}
};

