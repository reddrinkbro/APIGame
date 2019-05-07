#include "stdafx.h"
#include "hpPotion.h"

HRESULT hpPotion::init(void)
{
	_image = IMAGEMANAGER->addImage("hpPotion", "hpPotion.bmp", 28, 28, true, RGB(255, 0, 255));
	return S_OK;
}

void hpPotion::release(void)
{
}

void hpPotion::update(void)
{
	_rc = RectMakeCenter((int)_rcX, (int)_rcY, _image->getWidth(), _image->getHeight());
}

void hpPotion::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void hpPotion::setPotion(float* rcX, float* rcY)
{
	_rcX = rcX;
	_rcY = rcY;
	_cost = 1000;
	_recovery = 2.0f;
	_rc = RectMakeCenter(*_rcX, *_rcY, _image->getWidth(), _image->getHeight());
}


