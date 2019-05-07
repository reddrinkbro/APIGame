#include "stdafx.h"
#include "enemyManager.h"
#include "minion.h"

HRESULT enemyManager::init(void)
{
	IMAGEMANAGER->addImage("enemy", "enemySubmarine.bmp", 73, 51, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boat", "boat.bmp", 99, 61, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("helicopter", "helicopter.bmp", 68, 78, true, RGB(255, 255, 255));
	setMinion();
	return S_OK;
}

void enemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}
	for (_viBoat = _vBoat.begin(); _viBoat != _vBoat.end(); ++_viBoat)
	{
		(*_viBoat)->release();
		SAFE_DELETE(*_viBoat);
	}
	for (_viHeli = _vHeli.begin(); _viHeli != _vHeli.end(); ++_viHeli)
	{
		(*_viHeli)->release();
		SAFE_DELETE(*_viHeli);
	}
}

void enemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	
	for (_viBoat = _vBoat.begin(); _viBoat != _vBoat.end(); ++_viBoat)
	{
		(*_viBoat)->update();
	}
	for (_viHeli = _vHeli.begin(); _viHeli != _vHeli.end(); ++_viHeli)
	{
		(*_viHeli)->update();
	}
	addMinion();
	positionReset();
}

void enemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	for (_viBoat = _vBoat.begin(); _viBoat != _vBoat.end(); ++_viBoat)
	{
		
		(*_viBoat)->render();
	}
	for (_viHeli = _vHeli.begin(); _viHeli != _vHeli.end(); ++_viHeli)
	{
		(*_viHeli)->render();
	}
}

void enemyManager::setMinion(void)
{
	for (int i = 0; i < 4; i++)
	{
		enemy* enemy;
		enemy = new minion;
		if (i < 2)
		{
			enemy->init("enemy", PointMake(-RND->getInt(WINSIZEX), RND->getFromIntTo(WINSIZEY/2 -100,WINSIZEY - 100)));

		}
		else
		{
			enemy->init("enemy", PointMake(RND->getFromIntTo(WINSIZEX, WINSIZEX * 2), RND->getFromIntTo(WINSIZEY / 2 - 100, WINSIZEY - 100)));
		}
		_vMinion.push_back(enemy);
	}
	
	_enemyBoat = new enemyBoat;
	_enemyBoat->init("boat", PointMake(RND->getFromIntTo(WINSIZEX, WINSIZEX * 2), WINSIZEY / 2 - 100 - IMAGEMANAGER->findImage("boat")->getHeight() / 2));
	_vBoat.push_back(_enemyBoat);

	_enemyHelicopter = new enemyHelicopter;
	_enemyHelicopter->init("helicopter", PointMake(RND->getFromIntTo(WINSIZEX, WINSIZEX * 2), 100));
	_vHeli.push_back(_enemyHelicopter);
}

void enemyManager::addMinion(void)
{
	int randomSpawn = RND->getInt(10);
	if (_vMinion.size() < 4)
	{
		enemy* enemy;
		enemy = new minion;
		if (randomSpawn < 5)
		{
			enemy->init("enemy", PointMake(-RND->getInt(WINSIZEX), RND->getFromIntTo(WINSIZEY / 2 - 100, WINSIZEY - 100)));
		}
		else
		{
			enemy->init("enemy", PointMake(RND->getFromIntTo(WINSIZEX, WINSIZEX * 2), RND->getFromIntTo(WINSIZEY / 2 - 100, WINSIZEY - 100)));
		}
		_vMinion.push_back(enemy);
	}
	if (_vBoat.size() < 1)
	{
		_enemyBoat = new enemyBoat;
		_enemyBoat->init("boat", PointMake(RND->getFromIntTo(WINSIZEX, WINSIZEX * 2), WINSIZEY / 2 - 100 - IMAGEMANAGER->findImage("boat")->getHeight() / 2));
		_vBoat.push_back(_enemyBoat);
	}
	if (_vHeli.size() < 1)
	{
		_enemyHelicopter = new enemyHelicopter;
		_enemyHelicopter->init("helicopter", PointMake(RND->getFromIntTo(WINSIZEX, WINSIZEX * 2), 100));
		_vHeli.push_back(_enemyHelicopter);
	}
}

void enemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::removeBoat(int arrNum)
{
	SAFE_DELETE(_vBoat[arrNum]);
	_vBoat.erase(_vBoat.begin() + arrNum);
}

void enemyManager::removeHeli(int arrNum)
{
	SAFE_DELETE(_vHeli[arrNum]);
	_vHeli.erase(_vHeli.begin() + arrNum);
}

void enemyManager::positionReset(void)
{
	for (_viBoat = _vBoat.begin(); _viBoat != _vBoat.end();)
	{
		if ((*_viBoat)->getRect().right < 0)
		{
			SAFE_DELETE(*_viBoat);
			_vBoat.erase(_viBoat);
			break;
		}
		else
		{
			++_viBoat;
		}
	}
	for (_viHeli = _vHeli.begin(); _viHeli != _vHeli.end();)
	{
		if ((*_viHeli)->getRect().right < 0)
		{
			SAFE_DELETE(*_viHeli);
			_vHeli.erase(_viHeli);
			break;
		}
		else
		{
			++_viHeli;
		}
	}
}
