#include "stdafx.h"
#include "enemyManager.h"
#include "minion.h"

HRESULT enemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("jellyFish", "jellyFish.bmp",
		0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));

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
}

void enemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
}

void enemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
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
