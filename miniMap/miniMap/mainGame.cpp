#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//이곳에서 초기화

	_bgImage = new image;
	_bgImage->init("Blood.bmp", WINSIZEX, WINSIZEY);

	_MoveImage = new image;
	_MoveImage->init("11.bmp", 80, 70, true, RGB(255, 0, 255));

	_rc = RectMake(WINSIZEX/2, WINSIZEY / 2+184, 80, 70);
	_field = RectMake(0, WINSIZEY - 100, WINSIZEX, 100);
	_mini = RectMake(_rc.left, _rc.top, 160, 200);
	_count = 0;
	_alpha = 0;

	_count1 = 0;
	_alpha1 = 0;

	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용

	//이미지 삭제
	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_MoveImage);
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_rc.left += 5.0f;
		_rc.right += 5.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_rc.left -= 5.0f;
		_rc.right -= 5.0f;
	}

	_count++;
	if (_count % 3 == 0)
	{
		_alpha++;
		if (_alpha >= 255) _alpha = 0;
	}

	_count1++;
	if (_count1 % 3 == 0)
	{
		_alpha1 += 5;
		if (_alpha1 >= 255) _alpha1 = 0;
	}
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(HDC hdc)
{
	//백버퍼 가져오기 (이건 렌더에 그대로 둘것)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//흰색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	
	_bgImage->render(memDC);
	Rectangle(memDC, _field.left, _field.top, _field.right, _field.bottom);
	
	SetStretchBltMode(memDC, COLORONCOLOR);
	StretchBlt(memDC,0,0,160,140, memDC,0,0,WINSIZEX,WINSIZEY,SRCCOPY);
	_MoveImage->render(memDC, _rc.left, _rc.top);
	Rectangle(memDC, _rc.left*0.2, _rc.top*0.2, _rc.right*0.2, _rc.bottom*0.2);
	
	
	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(hdc);
}
