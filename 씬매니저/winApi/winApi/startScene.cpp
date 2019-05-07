#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init(void)
{
	_image = IMAGEMANAGER->addImage("startScene", "startScene.bmp", WINSIZEX, WINSIZEY);
	return S_OK;
}

void startScene::release(void)
{
}

void startScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		//¸ÊÃ¼ÀÎÁö
		SCENEMANAGER->changeScene("secondScene");
	}
}

void startScene::render(void)
{
	_image->render(getMemDC());
}
