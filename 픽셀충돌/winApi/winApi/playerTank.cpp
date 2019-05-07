#include "stdafx.h"
#include "playerTank.h"

HRESULT playerTank::init(void)
{

	_image = IMAGEMANAGER->addImage("tank", "tank.bmp", 70, 60, true, RGB(255, 0, 255));
	_angle = PI / 2;
	_tankCenterX = WINSIZEX / 2 + 250;
	_tankCenterY = WINSIZEY / 2 + 50;

	_rc = RectMakeCenter(_tankCenterX,_tankCenterY, _image->getWidth(), _image->getHeight());
	_probeY = _tankCenterY + _image->getHeight() / 2;
	_tankBullet = new tankBullet;
	_tankBullet->init(300,7);
	return S_OK;
}

void playerTank::release(void)
{
	//_tankBullet->release();
	//SAFE_DELETE(_tankBullet);
}

void playerTank::update(void)
{
	if (_tankCenterY > _ptMouse.y)
	{
		_angle = getAngle(_tankCenterX,_tankCenterY, _ptMouse.x, _ptMouse.y);
	}
	_tankEndX = _tankCenterX + cosf(_angle) * 40;
	_tankEndY =_tankCenterY - sinf(_angle) * 40;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_tankBullet->fire(_tankEndX, _tankEndY, _angle);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_tankCenterX += 1.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_tankCenterX -= 1.0f;
	}

	_probeY = _tankCenterY + _image->getHeight() / 2;

	//탐지할 Y값의 범위를 위아래로 원하는 만큼 검사
	for (int i = _probeY - 30; i < _probeY + 30; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("mountain")->getMemDC(), _tankCenterX, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_tankCenterY = i - _image->getHeight() / 2;
			break;
		}
	}

	_tankBullet->update();
	_rc = RectMakeCenter(_tankCenterX, _tankCenterY, _image->getWidth(), _image->getHeight());
}

void playerTank::render(void)
{
	LineMake(getMemDC(),_tankCenterX, _tankCenterY, _tankEndX, _tankEndY);
	_image->render(getMemDC(),_rc.left, _rc.top);
	_tankBullet->render();
}
