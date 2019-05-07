#include "stdafx.h"
#include "gameEndScene.h"

HRESULT gameEndScene::init(void)
{
	_winImage = IMAGEMANAGER->addImage("winImage", "win.bmp", WINSIZEX, WINSIZEY);
	_loseImage = IMAGEMANAGER->addImage("loseImage", "lose.bmp", WINSIZEX, WINSIZEY);
	_selectImage = 0;
	return S_OK;
}

void gameEndScene::release(void)
{
}

void gameEndScene::update(void)
{
}

void gameEndScene::render(void)
{
	if (_selectImage == 0)		//½Â¸®
	{
		_winImage->render(getMemDC());
	}
	else						//ÆĞ¹è
	{
		_loseImage->render(getMemDC());
	}
}
