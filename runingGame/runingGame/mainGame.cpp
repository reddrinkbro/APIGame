#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("������", "mario.bmp", 66, 84, 3, 4, true,RGB(255,0,255));
	IMAGEMANAGER->addImage("�ʵ�", "field.bmp", WINSIZEX, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��", "enemy.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���", "���.bmp", 2400, WINSIZEY - 100);
	_player.rc = RectMake(100, WINSIZEY - 100, 22, 84);
	field = RectMake(0, WINSIZEY - 100, WINSIZEX, WINSIZEY);
	_jumpCount = 0;
	_player.bulletAngle = PI / 2;
	_player.time = 0;
	_player.isJump = false;
	_player.gravity = 9.8f;
	_score = 0;
	_offsetX = _offsetY = 0;
	_bgSpeed = 0;
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
	_offsetX++;
	_bgSpeed += 3;
	_enemy = RectMake(RND->getFromIntTo(WINSIZEX, WINSIZEX * 2), WINSIZEY - 120, 20, 20);
	enemyCreate();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�		
	intersect();
	RECT rcTemp;
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_player.isJump = true;
		_jumpCount++;
		if (_jumpCount == 2)
		{
			this->doubleJump();
			_jumpCount++;
		}
	}
	if (_player.isJump) // �����Ҷ�
	{
		_player.time += 0.03;
		jump();
		IMAGEMANAGER->findImage("������")->setFrameX(0);
		IMAGEMANAGER->findImage("������")->setFrameY(3);
	}
	else
	{
		_count++;
		IMAGEMANAGER->findImage("������")->setFrameY(0);
		//�ִϸ��̼� �ӵ�
		if (_count % 6 == 0)
		{
			_index--;
			if (_index < 0)
			{
				_index = 2;
			}
			IMAGEMANAGER->findImage("������")->setFrameX(_index);
		}
	}
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	RECT rcTemp;
	//��� �� ��Ʈ�� (�̰͵� ������ �״�� �Ѱ�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	IMAGEMANAGER->loopRender("���", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _bgSpeed, 0);
	//IMAGEMANAGER->render("���",getMemDC());
	sprintf(str, "���� ���� : %d", _score);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
	IMAGEMANAGER->render("�ʵ�",getMemDC(), field.left, field.top);
	for (int i = 0; i < _enemyVec.size(); i++)
	{
		IMAGEMANAGER->render("��", getMemDC(), _enemyVec[i].left - 5, _enemyVec[i].top - 5);
	}
	IMAGEMANAGER->frameRender("������",getMemDC(), _player.rc.left, _player.rc.top);
	

	for (int i = 0; i < _enemyVec.size(); i++)
	{
		if (IntersectRect(&rcTemp, &_player.rc, &_enemyVec[i]))
		{
			Sleep(1000);
			Rectangle(getMemDC(), WINSIZEX / 2 - 100, WINSIZEY / 2 - 100, WINSIZEY / 2 + 100, WINSIZEY / 2 + 100);
			TextOut(hdc, WINSIZEX/2, WINSIZEY/2, "���� ����", strlen("���� ����"));
			exit(0);
		}
	}
	//=============================================================
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(getHDC());
}
void mainGame::jump(void)
{
	_player.rc.left = cosf(_player.bulletAngle) * 5 + _player.rc.left;
	_player.rc.right = cosf(_player.bulletAngle) * 5 + _player.rc.right;
	_player.rc.bottom = -(sinf(_player.bulletAngle) * 5 - (_player.gravity*_player.time)) + _player.rc.bottom;
	_player.rc.top = -(sinf(_player.bulletAngle) * 5 - (_player.gravity*_player.time)) + _player.rc.top;
}

void mainGame::intersect(void)
{
	RECT rcTemp;
	if (IntersectRect(&rcTemp, &_player.rc, &field))
	{
		_player.rc.bottom = field.top;
		_player.rc.top = _player.rc.bottom - 20;
		_player.time = 0;
		_player.isJump = false;
		_jumpCount = false;
	}
}

void mainGame::enemyCreate(void)
{
	if(_enemyVec.size() < ENEMYMAX)
	{
		_enemyVec.push_back(_enemy);
	}
	for (int i = 0; i < _enemyVec.size(); i++)
	{
		_enemyVec[i].left-=3;
		_enemyVec[i].right-=3;
		if (_enemyVec[i].right < 0)
		{
			_enemyVec.erase(_enemyVec.begin() + i);
			_score++;
		}
	}
}

void mainGame::doubleJump(void)
{
	_player.time = 0;
	this->jump();
}
