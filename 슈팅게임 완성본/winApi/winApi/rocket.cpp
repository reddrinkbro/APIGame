#include "stdafx.h"
#include "rocket.h"

HRESULT rocket::init(void)
{
	_image = IMAGEMANAGER->addFrameImage("rocket", "rocket.bmp", 161, 43,4,1, true, RGB(153, 217, 234));

	_x = WINSIZEX / 2;
	_y = WINSIZEY - 100;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	
	_currentFrame = 0;
	_score = 0;
	_windHit = 0;

	_missile = new missileM1;
	_missile->init(10, 700);

	_enegyBall = new enegyBall;
	_enegyBall->init(3, 700);

	_setWeapon = MISSILE;

	_currentHp = 10;
	_maxHp = 10;

	_hpBar = new progressBar;
	_hpBar->init(_x, _y, 52, 4);

	return S_OK;
}

void rocket::release(void)
{

	_missile->release();
	SAFE_DELETE(_missile);

	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void rocket::update(void)
{
	_count++;
	if (_count % 10 == 0)
	{
		_currentFrame++;
		if (_currentFrame > _image->getMaxFrameX())
		{
			_currentFrame = 0;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZEX)
	{
		_x += ROCKETSPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0)
	{
		_x -= ROCKETSPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_y -= ROCKETSPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZEY)
	{
		_y += ROCKETSPEED;
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_setWeapon = MISSILE;
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_setWeapon = ENEGYBALL;
	}

	switch (_setWeapon)
	{
	case MISSILE:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_missile->fire(_x, _y - 60);
		}
	case ENEGYBALL:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_enegyBall->fire(_x, _y - 60);
		}
		break;
	}
	if (_windHit)
	{
		_x -= 80;
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_missile->update();
	_enegyBall->update();
	_hpBar->setX(_x - (_rc.right - _rc.left) / 2);
	_hpBar->setY(_y - 10 - (_rc.bottom - _rc.top) / 2);
	_hpBar->update();
	_hpBar->setGuage(_currentHp, _maxHp);
}

void rocket::render(void)
{
	char str[128];
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrame, 0);
	_missile->render();
	_enegyBall->render();
	_hpBar->render();
	sprintf(str, "SCORE : %d", _score);
	TextOut(getMemDC(), WINSIZEX - 100, 50,str,strlen(str));
}

void rocket::removeMissile(int arrNum)
{
	_missile->removeBullet(arrNum);
}

void rocket::removeEnegyBall(int arrNum)
{
	_enegyBall->removeBullet(arrNum);
}


