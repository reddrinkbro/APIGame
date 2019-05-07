#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화

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
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용

	_slt->release();
	SAFE_DELETE(_slt);
	_startScene->release();
	SAFE_DELETE(_startScene);
	_secondScene->release();
	SAFE_DELETE(_secondScene);
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	_slt->update();
	_gameNode->update();
	_player->update();
	sceneMove();
	save();
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(void)
{
	//검은색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	
	//IMAGEMANAGER->findImage("background")->render(getMemDC());

	RECT rc = { 0, 0, WINSIZEX, WINSIZEY };

	//IMAGEMANAGER->findImage("background")->render(getMemDC(), rc.left,rc.top);
	_gameNode->render();
	_slt->render();
	
	TIMEMANAGER->render(getMemDC());

	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(getHDC());
}
