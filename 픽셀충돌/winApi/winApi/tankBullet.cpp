#include "stdafx.h"
#include "tankBullet.h"

HRESULT tankBullet::init(float range, int bulletMax)
{
	_range = range;
	_bulletMax = bulletMax;
	return S_OK;
}

void tankBullet::release(void)
{
}

void tankBullet::update(void)
{
	move();
}

void tankBullet::render(void)
{
	draw();
}

void tankBullet::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet _bullet;
	ZeroMemory(&_bullet,sizeof(tagBullet));
	_bullet._image = new image;
	_bullet._image ->init("tankBullet.bmp", 17, 15, true, RGB(255, 0, 255));
	_bullet._x = x;
	_bullet._y = y;
	_bullet._angle = angle;
	_bullet._speed = 6.0f;
	_bullet._rc = RectMakeCenter(_bullet._x, _bullet._y, _bullet._image->getWidth(), _bullet._image->getHeight());
	_bullet._time = 0.0f;
	_bullet._probeY = _bullet._y + _bullet._image->getHeight() / 2;
	_vBullet.push_back(_bullet);

}

void tankBullet::move(void)
{ 
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();++_viBullet)
	{
		_viBullet->_time += 0.03;
		_viBullet->_x += cosf(_viBullet->_angle) * _viBullet->_speed;
		_viBullet->_y = -(sinf(_viBullet->_angle) * _viBullet->_speed - (3* _viBullet->_time)) + _viBullet->_y;
		_viBullet->_probeY = _viBullet->_y + _viBullet->_image->getHeight() / 2;
		_viBullet->_rc = RectMakeCenter(_viBullet->_x, _viBullet->_y, _viBullet->_image->getWidth(), _viBullet->_image->getHeight());
	}
}

void tankBullet::draw(void)
{
	for each(auto index in _vBullet)
	{
		index._image->render(getMemDC(), index._rc.left, index._rc.top);
	}

}

void tankBullet::remove(int arrNum)
{
	float angle = 0;
	for (int angle = 0; angle < 360; angle++)
	{
		for (int i = 0; i < 10; i++)
		{
			SetPixel(IMAGEMANAGER->findImage("mountain")->getMemDC(), _vBullet[arrNum]._x + cosf(angle) * i, _vBullet[arrNum]._y - sinf(angle) * i, RGB(255, 0, 255));
		}
	}
	SAFE_DELETE(_vBullet[arrNum]._image);
	_vBullet.erase(_vBullet.begin() + arrNum);
}

