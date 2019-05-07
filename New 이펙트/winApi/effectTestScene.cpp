#include "stdafx.h"
#include "effectTestScene.h"

HRESULT effectTestScene::init(void)
{
	IMAGEMANAGER->addImage("effectSample", "effectSample.bmp", 1040, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("explosion", "explosion.bmp", 4355, 135, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("FFX", "FFX.bmp", WINSIZEX, WINSIZEY);
	
	//_effect->init(IMAGEMANAGER->findImage("explosion"), 335, 135, 14);
	EFFECTMANAGER->addEffect("effectSample", "effectSample", 1040, 80, 80, 80, 14, 100);
	EFFECTMANAGER->addEffect("explosion", "explosion", 4355, 135, 335, 135, 14, 100);
	return S_OK;
}

void effectTestScene::release(void)
{
}

void effectTestScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		EFFECTMANAGER->play("explosion", _ptMouse.x, _ptMouse.y);
	}
	/*string effectName, const char* imageName, int imagewidth, int imageHeights, int effectWidth
		, int effectHeight, int fps, int buffer*/
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		EFFECTMANAGER->play("effectSample",_ptMouse.x, _ptMouse.y);
	}
	EFFECTMANAGER->update(TIMEMANAGER->getElapsedTime());
}

void effectTestScene::render(void)
{
	IMAGEMANAGER->render("FFX", getMemDC());
	EFFECTMANAGER->render();
}
