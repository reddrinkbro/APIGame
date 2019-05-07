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

	_player = new player;
	_player->init();

	_startScene = new startScene;
	_startScene->init(_player);

	_secondScene = new secondScene;
	_secondScene->init(_player);

	selectMap();

	_slt = new saveLoadTest;
	_slt->init();

	_save = false;
	
	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���

	_slt->release();
	SAFE_DELETE(_slt);
	_startScene->release();
	SAFE_DELETE(_startScene);
	_secondScene->release();
	SAFE_DELETE(_secondScene);
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	_slt->update();
	_gameNode->update();
	_player->update();
	sceneMove();
	save();
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

	//IMAGEMANAGER->findImage("background")->render(getMemDC(), rc.left,rc.top);
	_gameNode->render();
	_slt->render();
	
	TIMEMANAGER->render(getMemDC());

	//=============================================================
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(getHDC());
}
