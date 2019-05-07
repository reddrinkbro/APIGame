#include "stdafx.h"
#include "enemyBoat.h"

HRESULT enemyBoat::init(const char * imageName, POINT position)
{
	_boatImage = IMAGEMANAGER->findImage(imageName);
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y, _boatImage->getWidth(), _boatImage->getHeight());
	_boatBullet = new boatBullet;
	_boatBullet->init(1);
	return S_OK;
}

void enemyBoat::release(void)
{
	_boatBullet->release();
	SAFE_DELETE(_boatBullet);
}

void enemyBoat::update(void)
{
	
	move();
	_boatBullet->update();
	
}

void enemyBoat::render(void)
{
	
	draw();
	_boatBullet->render();
}

void enemyBoat::move(void)
{
	_rc.left--;
	_rc.right--;
}

void enemyBoat::draw(void)
{
	_boatImage->render(getMemDC(), _rc.left, _rc.top);
}
