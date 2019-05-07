#include "stdafx.h"
#include "speedPotion.h"

HRESULT speedPotion::init(void)
{
	_image = IMAGEMANAGER->addImage("speedPotion", "speedPotion.bmp", 28, 28, true, RGB(255, 0, 255));
	return S_OK;
}

void speedPotion::release(void)
{
}

void speedPotion::update(void)
{
	_rc = RectMakeCenter((int)_rcX, (int)_rcY, _image->getWidth(), _image->getHeight());
}

void speedPotion::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void speedPotion::setPotion(float * rcX, float * rcY)
{
	_rcX = rcX;
	_rcY = rcY;
	_cost = 500;
	_speed = 1.0f;
	_rc = RectMakeCenter(*_rcX, *_rcY, _image->getWidth(), _image->getHeight());
}
