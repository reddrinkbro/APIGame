#include "stdafx.h"
#include "option.h"

HRESULT option::init(void)
{
	_image = IMAGEMANAGER->addImage("¿É¼Ç", "option.bmp", 355, 287,true,RGB(255,0,255));
	
	_x = WINSIZEX / 2 - _image->getWidth() / 2;
	_y = WINSIZEY / 2 - _image->getHeight() / 2;
	for (int i = 0; i < 2; i++)
	{
		_rc[i] = RectMakeCenter(0, 0, 30, 30);
	}
	_show = 1;
	return S_OK;
}

void option::release(void)
{
}

void option::update(void)
{
	_rc[0] = RectMakeCenter(_x + 82, WINSIZEY/2 -32, 30, 30);
	_rc[1] = RectMakeCenter(_x + _image->getWidth() - 82, WINSIZEY / 2 -32, 30, 30);
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		if (_show == 1)
		{
			_show = 0;
		}
		else
		{
			_show = 1;
		}
	}
}

void option::render(void)
{
	if (_show == 0)
	{
		_image->render(getMemDC(), _x, _y);
	}
}
