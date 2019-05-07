#include "stdafx.h"
#include "thirdScene.h"


HRESULT thirdScene::init(void)
{
	_image = IMAGEMANAGER->addImage("thirdScene", "thirdScene.bmp", WINSIZEX, WINSIZEY);
	_x = 0;
	_y = 390;
	_buccanary = new buccanary;
	_buccanary->init();
	_player = new player;
	_player->init(&_x, &_y);
	_popUp = new popUp;
	_popUp->init();
	return S_OK;
}

void thirdScene::release(void)
{
	_buccanary->release();
	SAFE_DELETE(_buccanary);
	_player->release();
	SAFE_DELETE(_player);
	_popUp->release();
	SAFE_DELETE(_popUp);
}

void thirdScene::update(void)
{
	if (!_popUp->getIsShow())
	{
		_player->update();
	}
	_popUp->update();
	nextScene();
	popUpWindow();
}

void thirdScene::render(void)
{
	RECT _rcTemp;
	_image->render(getMemDC());
	if (IntersectRect(&_rcTemp, &_player->getRect(), &_buccanary->getRect()))
	{
		_popUp->render();
	}
	_buccanary->render();
	//Rectangle(getMemDC(), _player->getRect().left, _player->getRect().top, _player->getRect().right, _player->getRect().bottom);
	_player->render();
}

void thirdScene::nextScene(void)
{
}

void thirdScene::popUpWindow(void)
{
	//SCENEMANAGER->changeScene("endScene");
	RECT _rcTemp;
	if (IntersectRect(&_rcTemp, &_player->getRect(), &_buccanary->getRect()))
	{
		_popUp->showPopUp();
	}
	if (_popUp->getIsShow())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_popUp->getLeft(), _ptMouse))
			{
				SCENEMANAGER->changeScene("endScene");
			}
			else if (PtInRect(&_popUp->getRight(), _ptMouse))
			{
				SCENEMANAGER->changeScene("start");
			}
		}
	}
}
