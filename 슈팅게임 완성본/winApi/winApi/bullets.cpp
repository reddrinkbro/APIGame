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
	bullet.img->init("missile.bmp", 10, 14, true, RGB(255, 0, 255));
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


HRESULT enegyBall::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	return S_OK;
}

void enegyBall::release(void)
{
}

void enegyBall::update(void)
{
	move();
}

void enegyBall::render(void)
{
	draw();
}

void enegyBall::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new image;
	bullet.img->init("missile2.bmp", 12, 26, true, RGB(77, 109, 243));
	bullet.speed = 3.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(), bullet.img->getHeight());

	_vBullet.push_back(bullet);
}

void enegyBall::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->rc.left,
			_viBullet->rc.top);
	}
}

void enegyBall::move(void)
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

void enegyBall::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);

	_vBullet.erase(_vBullet.begin() + arrNum);
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

HRESULT bossBullet::init(int bulletMax)
{
	_bulletMax = bulletMax;
	
	return S_OK;
}

void bossBullet::release(void)
{
}

void bossBullet::update(void)
{
	move();
}

void bossBullet::render(void)
{
	draw();
}

void bossBullet::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	for (int i = 0; i < 7; i++)
	{
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.img = new image;
		bullet.img->init("bossBullet.bmp", 0.0f, 0.0f, 230, 36, 7,1, true, RGB(248, 0, 248));
		bullet.speed = 5.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.bulletNum = i;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
		_vBullet.push_back(bullet);
	}
}

void bossBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left,
			_viBullet->rc.top);

		_viBullet->img->setFrameX(_viBullet->bulletNum);
	}
}

void bossBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += _viBullet->bulletNum - 3;
		_viBullet->y += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		//사거리 밖으로 나갔음
		if (_viBullet->rc.top >WINSIZEY)
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void bossBullet::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);

	_vBullet.erase(_vBullet.begin() + arrNum);
}
