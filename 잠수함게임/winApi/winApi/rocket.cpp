#include "stdafx.h"
#include "rocket.h"

HRESULT rocket::init(void)
{
	_image = IMAGEMANAGER->addImage("rocket", "submarine.bmp", 59, 55, true, RGB(255, 255, 255));

	_x = WINSIZEX / 2;
	_y = WINSIZEY - 100;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	
	_currentFrame = 0;
	_score = 0;
	_windHit = 0;

	_missile = new missileM1;
	_missile->init(10, 700);

	_rocketLauncher = new rocketLauncher;
	_rocketLauncher->init(20, 700);

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
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZEX)
	{
		_x += ROCKETSPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0)
	{
		_x -= ROCKETSPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > WINSIZEY /2 -100)
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
		_setWeapon = MISSILE2;
	}

	switch (_setWeapon)
	{
	case MISSILE:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_missile->fire(_x, _y - 60);
		}
	case MISSILE2:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_rocketLauncher->fire(_x, _y - 60);
		}
		break;
	}
	if (_windHit)
	{
		_x -= 80;
	}

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_missile->update();
	_rocketLauncher->update();
	_hpBar->setX(_x - (_rc.right - _rc.left) / 2);
	_hpBar->setY(_y - 10 - (_rc.bottom - _rc.top) / 2);
	_hpBar->update();
	_hpBar->setGuage(_currentHp, _maxHp);
}

void rocket::render(void)
{
	char str[128];
	_image->render(getMemDC(), _rc.left, _rc.top);
	_missile->render();
	_rocketLauncher->render();
	_hpBar->render();
	sprintf(str, "SCORE : %d", _score);
	TextOut(getMemDC(), WINSIZEX - 100, 50,str,strlen(str));
	sprintf(str, "미사일 수 : %d" , _rocketLauncher->getBullet().size());
	TextOut(getMemDC(), WINSIZEX - 100, 70, str, strlen(str));
}

void rocket::removeMissile(int arrNum)
{
	_missile->removeBullet(arrNum);
}

void rocket::removeRocketLauncher(int arrNum)
{
	_rocketLauncher->removeBullet(arrNum);
}


