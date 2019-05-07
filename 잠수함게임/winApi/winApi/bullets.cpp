#include "stdafx.h"
#include "bullets.h"

HRESULT missileM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void missileM1::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void missileM1::update(void)
{
	move();
}

void missileM1::render(void)
{
	draw();
}

void missileM1::fire(float x, float y)
{
	//최대 발사 갯수를 막는다
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new image;
	bullet.img->init("missile.bmp", 17, 40, true, RGB(255, 255, 255));
	bullet.speed = 3.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(), bullet.img->getHeight());

	_vBullet.push_back(bullet);
}

void missileM1::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->rc.left,
			_viBullet->rc.top);
	}
}

void missileM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y + _viBullet->img->getHeight(),
			_viBullet->img->getWidth(), _viBullet->img->getHeight());

		//사거리 밖으로 나갔음
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y + 100))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void missileM1::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);

	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT rocketLauncher::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	for (int i = 0; i < _bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.img = new image;
		bullet.img->init("missile2.bmp", 18, 35, true, RGB(0, 248, 0));
		bullet.speed = 3.0f;
		bullet.fire = false;
		_vBullet.push_back(bullet);

	}
	return S_OK;
}

void rocketLauncher::release(void)
{
}

void rocketLauncher::update(void)
{
	move();
}

void rocketLauncher::render(void)
{
	draw();
}

void rocketLauncher::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire)continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());
		break;
	}
}

void rocketLauncher::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->img->render(getMemDC(), _viBullet->rc.left,
			_viBullet->rc.top);
	}
}

void rocketLauncher::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y + _viBullet->img->getHeight(),
			_viBullet->img->getWidth(), _viBullet->img->getHeight());

		//사거리 밖으로 나갔음
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y + 100))
		{
			_vBullet.erase(_viBullet);
			break;
		}
	}
}

void rocketLauncher::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);

	_vBullet.erase(_vBullet.begin() + arrNum);
}

void rocketLauncher::addBullet(void)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new image;
	bullet.img->init("missile2.bmp", 18, 35, true, RGB(0, 248, 0));
	bullet.speed = 3.0f;
	bullet.fire = false;
	_vBullet.push_back(bullet);
}


HRESULT enemyBullet::init(int bulletMax)
{
	_bulletMax = bulletMax;
	_time = RND->getFromFloatTo(5.0f, 10.0f);
	return S_OK;
}

void enemyBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void enemyBullet::update(void)
{
	_time-=0.1;
	if (_time < 0)
	{
		move();
	}
}

void enemyBullet::render(void)
{
	if (_time < 0)
	{
		draw();
	}
}

void enemyBullet::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new image;
	bullet.img->init("enemyBullet.bmp", 17, 15, true, RGB(255, 0, 255));
	bullet.angle = angle;
	bullet.speed = 3.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());

	_vBullet.push_back(bullet);
}

void enemyBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void enemyBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());

		//사거리 밖으로 나갔음
		if (_viBullet->rc.top >WINSIZEY)
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void enemyBullet::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);

	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT boatBullet::init(int bulletMax)
{
	_bulletMax = bulletMax;
	
	return S_OK;
}

void boatBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void boatBullet::update(void)
{
	move();
}

void boatBullet::render(void)
{
	draw();
}

void boatBullet::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new image;
	bullet.img->init("boatBullet.bmp", 23, 36, true, RGB(248, 0, 248));
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
	_vBullet.push_back(bullet);
	
}

void boatBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void boatBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y +=_viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());

		//사거리 밖으로 나갔음
		if (_viBullet->rc.top >WINSIZEY)
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void boatBullet::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);

	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT helicopterBullet::init(int bulletMax)
{
	_bulletMax = bulletMax;
	return S_OK;
}

void helicopterBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void helicopterBullet::update(void)
{
	move();
}

void helicopterBullet::render(void)
{
	draw();
}

void helicopterBullet::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new image;
	bullet.img->init("helicopterBullet.bmp", 20, 67, true, RGB(0, 248, 0));
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
	_vBullet.push_back(bullet);
}

void helicopterBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void helicopterBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());

		//사거리 밖으로 나갔음
		if (_viBullet->rc.top >WINSIZEY)
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void helicopterBullet::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);

	_vBullet.erase(_vBullet.begin() + arrNum);
}
