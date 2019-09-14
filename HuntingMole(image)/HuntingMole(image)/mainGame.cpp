#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//�̰����� �ʱ�ȭ
	_hammer = new image;
	_hammer->init("��ġ.bmp",60,60,true,RGB(255,0,255));
	_catch = new image;
	_catch->init("����.bmp", 100, 100, true, RGB(255, 0, 255));
	_mole = new image;
	_mole->init("�δ���.bmp", 100, 100, true, RGB(255, 0, 255));
	_tunnul = new image;
	_tunnul->init("��.bmp", 100, 100, true, RGB(255, 0, 255));
	
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
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���
	SAFE_DELETE(_hammer);
	SAFE_DELETE(_catch);
	SAFE_DELETE(_mole);
	SAFE_DELETE(_tunnul);
	//�̹��� ����
	
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�

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
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	//����� �������� (�̰� ������ �״�� �Ѱ�)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//��� �� ��Ʈ�� (�̰͵� ������ �״�� �Ѱ�)
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
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(hdc);
}
