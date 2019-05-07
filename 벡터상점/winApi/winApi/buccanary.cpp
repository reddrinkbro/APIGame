#include "stdafx.h"
#include "buccanary.h"

HRESULT buccanary::init(void)
{
	_image = IMAGEMANAGER->addImage("buccanary", "buccanary.bmp", 32, 57, true, RGB(255, 0, 255));
	_rc = RectMakeCenter(WINSIZEX/2, WINSIZEY / 2 + 130,_image->getWidth(),_image->getHeight());
	return S_OK;
}

void buccanary::release(void)
{
}

void buccanary::update(void)
{
}

void buccanary::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}
