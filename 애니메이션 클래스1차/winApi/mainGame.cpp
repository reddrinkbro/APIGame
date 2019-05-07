#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ

	IMAGEMANAGER->addImage("background", "background.bmp", WINSIZEX, WINSIZEY);
	
	_rocket = new rocket;
	_rocket->init();
	
	_em = new enemyManager;
	_em->init();

	_at = new animationTest;
	_at->init();

	_x = _y = 0.0f;

	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���

	_rocket->release();
	SAFE_DELETE(_rocket);

	_em->release();
	SAFE_DELETE(_em);

	_at->release();
	SAFE_DELETE(_at);
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�

	_rocket->update();

	_em->update();

	_at->update();

	collision();

	_y -= 1.0f;
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(void)
{
	//������ �� ��Ʈ�� (�̰͵� ������ �״�� �Ѱ�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	
	//IMAGEMANAGER->findImage("background")->render(getMemDC());

	RECT rc = { 0, 0, WINSIZEX, WINSIZEY };
	IMAGEMANAGER->findImage("background")->loopRender(getMemDC(), &rc, _x, _y);

	_rocket->render();

	_em->render();

	_at->render();

	TIMEMANAGER->render(getMemDC());

	//=============================================================
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(getHDC());
}
