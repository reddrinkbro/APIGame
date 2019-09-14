#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ
	IMAGEMANAGER->addImage("�÷��̾�", "�÷��̾�.bmp", 43, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��", "��.bmp", 43, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���", "����.bmp", 255, 2400);
	IMAGEMANAGER->addImage("�����", "�����.bmp", 150, 130);
	IMAGEMANAGER->addImage("ȭ��ǥ", "ȭ��ǥ.bmp", 18, 62, true, RGB(255, 0, 255));
	_player = RectMake(WINSIZEX / 2, WINSIZEY - 200, 43, 83);
	_arrow.start.x = 70;
	_arrow.start.y = WINSIZEY - 23;
	_arrow.angle = PI /6 * 5;		 
	_arrow.length = 70;				 
	_arrow.radius = 1;				 		
	_score = 0;
	_offsetX = _offsetY = 0;
	_bgSpeed = 0;
	_speed = 3;
	isSpeedDown = false;
	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	
	_bgSpeed -= _speed;
	_enemy = RectMake(RND->getFromIntTo(WINSIZEX / 2 - 112, WINSIZEX / 2 + 112), -RND->getFromIntTo(0, 2 * WINSIZEY) ,43, 83);
	_arrow.end.x = cosf(_arrow.angle) * _arrow.length + _arrow.start.x;
	_arrow.end.y = -sinf(_arrow.angle) * _arrow.length + _arrow.start.y;
	enemyCreate();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�		
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player.left > WINSIZEX / 2 - 112)
	{
		_player.left -= 3;
		_player.right -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player.left < WINSIZEX / 2 + 112)
	{
		_player.left += 3;
		_player.right += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_speed += 0.1f;
		_arrow.angle-=0.01f;
		isSpeedDown = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		isSpeedDown = true;
	}
	if (isSpeedDown)
	{
		if (_arrow.angle <PI / 6 * 5)
		{
			_arrow.angle += 0.01f;
		}
		if (_speed > 3)
		{
			_speed -= 0.1f;
		}
	}
	if (_arrow.angle < PI / 3)
	{
		_arrow.angle += 0.01f;
	}
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	RECT rcTemp;
	HPEN Brush;
	//��� �� ��Ʈ�� (�̰͵� ������ �״�� �Ѱ�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	Rectangle(getMemDC(),0 ,0 , WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("���", getMemDC(), &RectMake(WINSIZEX / 2 - 112, 0, 255, WINSIZEY), 0, _bgSpeed);
	IMAGEMANAGER->render("�����", getMemDC(), 0, WINSIZEY - 130);
	LineMake(getMemDC(), _arrow.start.x, _arrow.start.y, _arrow.end.x, _arrow.end.y);
	sprintf(str, "���� ���� : %d", _score);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
	
	for (int i = 0; i < _enemyVec.size(); i++)
	{
		IMAGEMANAGER->render("��", getMemDC(), _enemyVec[i].left, _enemyVec[i].top);
	}

	IMAGEMANAGER->render("�÷��̾�",getMemDC(), _player.left, _player.top);
	
	for (int i = 0; i < _enemyVec.size(); i++)
	{
		/*if (IntersectRect(&rcTemp, &_player, &_enemyVec[i]))
		{
			Sleep(1000);
			Rectangle(getMemDC(), WINSIZEX / 2 - 100, WINSIZEY / 2 - 100, WINSIZEY / 2 + 100, WINSIZEY / 2 + 100);
			TextOut(hdc, WINSIZEX/2, WINSIZEY/2, "���� ����", strlen("���� ����"));
			exit(0);
		}*/
	}
	//=============================================================
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(getHDC());
}



void mainGame::enemyCreate(void)
{
	RECT rcTemp;
	if(_enemyVec.size() < ENEMYMAX)
	{
		_enemyVec.push_back(_enemy);
	}
	for (int i = 0; i < _enemyVec.size(); i++)
	{
		_enemyVec[i].top += _speed;
		_enemyVec[i].bottom += _speed;
		for (int j = i + 1; j < _enemyVec.size() - 1; j++)
		{
			if (IntersectRect(&rcTemp, &_enemyVec[i], &_enemyVec[j]))
			{
				_enemyVec[i].top = _enemyVec[j].top- 83;
				_enemyVec[i].bottom = _enemyVec[j].bottom-83;
			}
			if (_enemyVec[i].bottom > WINSIZEY * 2)
			{
				_enemyVec.erase(_enemyVec.begin() + i);
				_score++;
			}
		}
	}
}
