#include "stdafx.h"
#include "enemyManager.h"
#include "minion.h"
#include "rocket.h"

HRESULT enemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("jellyFish", "jellyFish.bmp",
		0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));

	setMinion();

	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 7, 7, true, RGB(255, 0, 255));
	_bullet = new bullet;
	_bullet->init("bullet", 30, 1000);

	return S_OK;
}

void enemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}

	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}

	minionBulletFire();
	_bullet->update();

	//collision();
}

void enemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
}

void enemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			enemy* jellyFish;
			jellyFish = new minion;
			jellyFish->init("jellyFish", PointMake(100 + j * 100, 100 + i * 100));
			_vMinion.push_back(jellyFish);
		}
	}
}

void enemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();

			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				getAngle(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2,
					_rocket->getPosition().x, _rocket->getPosition().y),
				RND->getFromFloatTo(2.0f, 4.0f));
		}
	}
}

void enemyManager::collision(void)
{
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
			&_rocket->getRect()))
		{
			_bullet->removeBullet(i);
			_rocket->hitDamage(2.0f);
		}
	}
}
