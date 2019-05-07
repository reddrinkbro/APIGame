#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init(void)
{
	_hpPotion = new hpPotion;
	_hpPotion->init();
	_speedPotion = new speedPotion;
	_speedPotion->init();
	_sword = new sword;
	_sword->init();
	return S_OK;
}

void itemManager::release(void)
{
	_hpPotion->release();
	SAFE_DELETE(_hpPotion);
	_speedPotion->release();
	SAFE_DELETE(_speedPotion);
	_sword->release();
	SAFE_DELETE(_sword);
}

void itemManager::update(void)
{
	_hpPotion->update();
	_speedPotion->update();
	_sword->update();
}

void itemManager::render(void)
{
	_hpPotion->render();
	_speedPotion->render();
	_sword->render();
}
