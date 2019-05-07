#include "stdafx.h"
#include "endScene.h"


HRESULT endScene::init(void)
{
	_image = IMAGEMANAGER->addImage("endScene", "endScene.bmp", WINSIZEX, WINSIZEY,true,RGB(255,0,255));
	_imageDie = IMAGEMANAGER->addImage("Die", "Die.bmp", 512, 64);
	_x = 33;
	_y = 390;
	_player = new player;
	_player->init(&_x,&_y);
	_time = TIMEMANAGER->getWorldTime() + 5;
	return S_OK;
}

void endScene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
}

void endScene::update(void)
{
	if (_player->getCurrentHp() > 0)
	{
		_player->update();
	}
	_player->showProgressBar(0.03);
	nextScene();
}

void endScene::render(void)
{
	_image->render(getMemDC());
	_player->render();
	if (_player->getCurrentHp() <= 0)
	{
		_imageDie->render(getMemDC(), WINSIZEX / 2 - _imageDie->getWidth()/2, WINSIZEY / 2 );
	}
}

void endScene::nextScene(void)
{
	if (_player->getCurrentHp() <= 0 && TIMEMANAGER->getWorldTime() >= _time)
	{
		SCENEMANAGER->changeScene("start");
	}
}
