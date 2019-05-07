#include "stdafx.h"
#include "popUp.h"

HRESULT popUp::init(void)
{
	_image = IMAGEMANAGER->addImage("popUp", "popUp.bmp", 512, 64, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2 - _image->getWidth() / 2;
	_y = WINSIZEY / 2 - _image->getHeight() / 2;
	for (int i = 0; i < 2; i++)
	{
		_rc[i] = RectMakeCenter(0, 0, 30, 30);
	}
	_isShow = false;
	return S_OK;
}

void popUp::release(void)
{
}

void popUp::update(void)
{
	_rc[0] = RectMakeCenter(_x+124, WINSIZEY / 2, 185, 21);
	_rc[1] = RectMakeCenter(_x + _image->getWidth()-124 , WINSIZEY / 2, 185, 21);
}

void popUp::render(void)
{
	
	_image->render(getMemDC(), _x, _y);
	for (int i = 0; i < 2; i++)
	{
	//	Rectangle(getMemDC(), _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}
}

void popUp::showPopUp(void)
{
	_isShow = true;
}
