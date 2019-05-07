#include "stdafx.h"
#include "sword.h"

HRESULT sword::init(void)
{
	_image = IMAGEMANAGER->addImage("hat", "hat.bmp", 32, 32, true, RGB(255, 0, 255));
	return S_OK;
}

void sword::release(void)
{
}

void sword::update(void)
{
	_rc = RectMakeCenter((int)_rcX, (int)_rcY, _image->getWidth(), _image->getHeight());
}

void sword::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void sword::setSword(float * rcX, float * rcY)
{
	_rcX = rcX;
	_rcY = rcY;
	_cost = 700;
	_atk = 2.0f;
	_rc = RectMakeCenter(*_rcX, *_rcY, _image->getWidth(), _image->getHeight());
}
