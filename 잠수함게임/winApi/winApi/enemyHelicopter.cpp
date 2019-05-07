#include "stdafx.h"
#include "enemyHelicopter.h"


HRESULT enemyHelicopter::init(const char * imageName, POINT position)
{
	_boatImage = IMAGEMANAGER->findImage(imageName);
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y, _boatImage->getWidth(), _boatImage->getHeight());
	_helicopterBullet = new helicopterBullet;
	_helicopterBullet->init(1);
	return S_OK;
}

void enemyHelicopter::release(void)
{
	_helicopterBullet->release();
	SAFE_DELETE(_helicopterBullet);
}

void enemyHelicopter::update(void)
{
	move();
	_helicopterBullet->update();
}

void enemyHelicopter::render(void)
{
	draw();
	_helicopterBullet->render();
}

void enemyHelicopter::move(void)
{
	_rc.left -= 2;
	_rc.right -= 2;
}

void enemyHelicopter::draw(void)
{
	_boatImage->render(getMemDC(), _rc.left, _rc.top);
}
