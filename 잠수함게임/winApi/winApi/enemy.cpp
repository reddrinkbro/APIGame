#include "stdafx.h"
#include "enemy.h"

enemy::enemy() : _x(0.0f),
				 _y(0.0f),
				 _rc(RectMake(0, 0, 0, 0)),
				 _randDomDirction(RND->getInt(2))
{
}


HRESULT enemy::init(void)
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y,
		_image->getWidth(), _image->getHeight());

	_enemyBullet = new enemyBullet;
	_enemyBullet->init(1);
	return S_OK;
}

void enemy::release(void)
{
	_enemyBullet->release();
	SAFE_DELETE(_enemyBullet);
}

void enemy::update(void)
{
	move();
	_enemyBullet->update();
}

void enemy::render(void)
{
	draw();
	_enemyBullet->render();
}

//에너미마다 움직임이 틀리니 상속받아 자식에서 구현
void enemy::move(void)
{
	if (_randDomDirction == 0)
	{
		_rc.left--;
		_rc.right--;
		if(_rc.left<-WINSIZEX /2)
		{
			_randDomDirction = 1;
		}
	}
	else
	{
		_rc.left++;
		_rc.right++;
		if (_rc.right > WINSIZEX + WINSIZEX/2)
		{
			_randDomDirction = 0;
		}
	}
}

void enemy::draw(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void enemy::removeMissile(int arrNum)
{
	_enemyBullet->removeBullet(arrNum);
}