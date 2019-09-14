#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//이곳에서 초기화
	_hammer = new image;
	_hammer->init("망치.bmp",60,60,true,RGB(255,0,255));
	_catch = new image;
	_catch->init("정답.bmp", 100, 100, true, RGB(255, 0, 255));
	_mole = new image;
	_mole->init("두더지.bmp", 100, 100, true, RGB(255, 0, 255));
	_tunnul = new image;
	_tunnul->init("굴.bmp", 100, 100, true, RGB(255, 0, 255));
	
	_currentRect = CURRENTRECT_NULL;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_rc[i * 4 + j] = RectMakeCenter(100 + j * 200, 200 + i * 200, 200, 200);
		}
	}

	_index = 0;
	_count = 0;
	_time = RND->getFromIntTo(30, 90);

	_isSelected = false;
	_isOnceCheck = false;

	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용
	SAFE_DELETE(_hammer);
	SAFE_DELETE(_catch);
	SAFE_DELETE(_mole);
	SAFE_DELETE(_tunnul);
	//이미지 삭제
	
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc[_index], _ptMouse) && !_isOnceCheck)
		{
			_isOnceCheck = true;
		}
	}
	if (!_isSelected)
	{
		_count++;
		if (_count%_time == 0)
		{
			_count = 0;
			_index = RND->getInt(8);
			_currentRect = (CURRENTRECT)_index;
			_isSelected = true;
		}	
	}
	else
	{
		_count++;
		if (_count % _time == 0)
		{
			_isOnceCheck = false;
			_isSelected = false;
			_currentRect = CURRENTRECT_NULL;
			_time = RND->getFromIntTo(30, 60);
			_index = 100;
		}
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
	ShowCursor(false);
	for (int i = 0;i < 8;i++)
	{
		Rectangle(memDC, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}
	
	for (int i = 0;i < 8;i++)
	{
		if (i == _index)_mole->render(memDC, _rc[i].left, _rc[i].top);
		else if(i != _index)
		{
			_tunnul->render(memDC, _rc[i].left, _rc[i].top);
		}
	}
	if (_isOnceCheck)
	{
		_catch->render(memDC, _rc[_index].left, _rc[_index].top);
	}
	_hammer->render(memDC, _ptMouse.x - 30, _ptMouse.y - 15);
	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(hdc);
}
