#include "stdafx.h"
#include "secondScene.h"

HRESULT secondScene::init(void)
{
	IMAGEMANAGER->addImage("background", "background.bmp", WINSIZEX, WINSIZEY);


	//루프 변수들 초기화
	_offsetX = _offsetY = 0;

	return S_OK;
}

void secondScene::release(void)
{

}

void secondScene::update(void)
{
	_offsetX -= 1.0f;
}

void secondScene::render(void)
{
	RECT rc = { 0, 0, WINSIZEX, WINSIZEY};
	IMAGEMANAGER->findImage("background")->loopRender(getMemDC(), &rc, _offsetX, _offsetY);

}
