#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init(void)
{
	IMAGEMANAGER->addImage("��ŸƮ", "image/����ȭ��.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("����", "image/����(����).bmp", 1000, 100, true, RGB(255, 0, 255));

	_alpha = 255;

	wsprintf(_text, "���Ⱑ ��ŸƮ��");

	return S_OK;
}

void startScene::release(void)
{
}

void startScene::update(void)
{
	_alpha -= 3.0f;
	if (_alpha <= 0) _alpha = 255;
}

void startScene::render(void)
{
	IMAGEMANAGER->render("��ŸƮ", getMemDC());
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, _text, strlen(_text));
	IMAGEMANAGER->alphaRender("����", getMemDC(), 130, WINSIZEY / 2 + 200, _alpha);
}
