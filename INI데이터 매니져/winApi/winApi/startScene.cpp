#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init(player* player)
{
	IMAGEMANAGER->addImage("스타트", "background.bmp", WINSIZEX, WINSIZEY);
	_rc = RectMake(WINSIZEX / 2 - 40, WINSIZEY / 2 + 110, 70, 72);

	_player = player;

	_itemManager = new itemManager;
	_itemManager->init();
	_renderValue = INIDATA->loadDataIntrger("option","mapLight","key");
	return S_OK;
}

void startScene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);

	_itemManager->release();
	SAFE_DELETE(_itemManager);
}

void startScene::update(player* player)
{
	player->update();
	_itemManager->update();
}

void startScene::render(void)
{
	IMAGEMANAGER->alphaRender("스타트", getMemDC(), _renderValue);
	_itemManager->render();
	_player->render();
}
