#include "stdafx.h"
#include "secondScene.h"

HRESULT secondScene::init(void)
{
	IMAGEMANAGER->addImage("스타트", "background.bmp", WINSIZEX, WINSIZEY);
	_x = 33; 
	_y = 450;
	_player = new player;
	_player->init(&_x, &_y);
	_itemManager = new itemManager;
	_itemManager->init();
	
	return S_OK;
}

void secondScene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);

	_itemManager->release();
	SAFE_DELETE(_itemManager);
}

void secondScene::update(void)
{
	_player->update();
	_itemManager->update();
	nextScene();
}

void secondScene::render(void)
{
	IMAGEMANAGER->render("스타트", getMemDC());
	_itemManager->render();
	_player->render();
}

void secondScene::nextScene(void)
{
	if (_player->getRect().left > WINSIZEX)
	{
		SCENEMANAGER->changeScene("thirdScene");
	}
}
