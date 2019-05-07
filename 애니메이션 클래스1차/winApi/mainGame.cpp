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
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용

	_rocket->release();
	SAFE_DELETE(_rocket);

	_em->release();
	SAFE_DELETE(_em);

	_at->release();
	SAFE_DELETE(_at);
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다

	_rocket->update();

	_em->update();

	_at->update();

	collision();

	_y -= 1.0f;
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
	IMAGEMANAGER->findImage("background")->loopRender(getMemDC(), &rc, _x, _y);

	_rocket->render();

	_em->render();

	_at->render();

	TIMEMANAGER->render(getMemDC());

	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(getHDC());
}
