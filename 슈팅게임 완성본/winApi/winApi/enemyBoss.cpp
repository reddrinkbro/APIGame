#include "stdafx.h"
#include "enemyBoss.h"

HRESULT enemyBoss::init(const char * imageName, POINT position)
{
	_bossImage = IMAGEMANAGER->findImage(imageName);
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y, _bossImage->getWidth(), _bossImage->getHeight());
	_currentHp = 50;
	_maxHp = 50;
	_isAppear = false;
	_progressBar = new bossProgressBar;
	_progressBar->init(_x, _y, 156, 4);
	_bossBullet = new bossBullet;
	_bossBullet->init(1);
	return S_OK;
}

void enemyBoss::release(void)
{
	_progressBar->release();
	SAFE_DELETE(_progressBar);
	_bossBullet->release();
	SAFE_DELETE(_bossBullet);
}

void enemyBoss::update(void)
{
	if (_isAppear)
	{
		move();
		_bossBullet->update();
		_progressBar->setX(_rc.left + 15);
		_progressBar->setY(_rc.top - 25);
		_progressBar->update();
		_progressBar->setGuage(_currentHp, _maxHp);
	}
}

void enemyBoss::render(void)
{
	if (_isAppear)
	{
		draw();
		_bossBullet->render();
		_progressBar->render();
	}
	
}

void enemyBoss::move(void)
{
	if (_rc.bottom < 150)
	{
		_rc.top++;
		_rc.bottom++;
	}
}

void enemyBoss::draw(void)
{
	_bossImage->render(getMemDC(), _rc.left, _rc.top);
}
