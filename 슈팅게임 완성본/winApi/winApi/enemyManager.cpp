#include "stdafx.h"
#include "enemyManager.h"
#include "minion.h"

HRESULT enemyManager::init(void)
{
	IMAGEMANAGER->addImage("enemy", "enemy.bmp", 67, 55, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss", "boss.bmp", 180, 95, true, RGB(255, 0, 255));
	setMinion();
	_enemyBoss = new enemyBoss;
	_enemyBoss->init("boss", PointMake(304,-100));
	return S_OK;
}

void enemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}
	_enemyBoss->release();
	SAFE_DELETE(_enemyBoss);
}

void enemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	addMinion();
	_enemyBoss->update();
}

void enemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_enemyBoss->render();
}

void enemyManager::setMinion(void)
{
	for (int i = 0; i < 10; i++)
	{
		enemy* enemy;
		enemy = new minion;
		if (i < 5)
		{
			enemy->init("enemy", PointMake(100 + i * 100, 200));
		}
		else
		{
			enemy->init("enemy", PointMake(100 + (i - 5) * 100, 400));
		}
		_vMinion.push_back(enemy);
	}
}

void enemyManager::addMinion(void)
{
	int randomSpawn = RND->getInt(10);
	if (_vMinion.size() < 10)
	{
		enemy* enemy;
		enemy = new minion;
		if (randomSpawn < 5)
		{
			enemy->init("enemy", PointMake(100 + randomSpawn * 100, 200));
		}
		else
		{
			enemy->init("enemy", PointMake(100 + (randomSpawn - 5) * 100, 400));
		}
		_vMinion.push_back(enemy);
	}
}

void enemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::appearBoss(void)
{
	_enemyBoss->setIsAppear(true);
}
