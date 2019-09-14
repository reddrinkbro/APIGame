#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화
	IMAGEMANAGER->addFrameImage("마리오", "mario.bmp", 66, 84, 3, 4, true,RGB(255,0,255));
	IMAGEMANAGER->addImage("필드", "field.bmp", WINSIZEX, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("적", "enemy.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경", "배경.bmp", 2400, WINSIZEY - 100);
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
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	_offsetX++;
	_bgSpeed += 3;
	_enemy = RectMake(RND->getFromIntTo(WINSIZEX, WINSIZEX * 2), WINSIZEY - 120, 20, 20);
	enemyCreate();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다		
	intersect();
	RECT rcTemp;
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
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
	if (_player.isJump) // 점프할때
	{
		_player.time += 0.03;
		jump();
		IMAGEMANAGER->findImage("마리오")->setFrameX(0);
		IMAGEMANAGER->findImage("마리오")->setFrameY(3);
	}
	else
	{
		_count++;
		IMAGEMANAGER->findImage("마리오")->setFrameY(0);
		//애니메이션 속도
		if (_count % 6 == 0)
		{
			_index--;
			if (_index < 0)
			{
				_index = 2;
			}
			IMAGEMANAGER->findImage("마리오")->setFrameX(_index);
		}
	}
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	RECT rcTemp;
	//흰색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	IMAGEMANAGER->loopRender("배경", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _bgSpeed, 0);
	//IMAGEMANAGER->render("배경",getMemDC());
	sprintf(str, "현재 점수 : %d", _score);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
	IMAGEMANAGER->render("필드",getMemDC(), field.left, field.top);
	for (int i = 0; i < _enemyVec.size(); i++)
	{
		IMAGEMANAGER->render("적", getMemDC(), _enemyVec[i].left - 5, _enemyVec[i].top - 5);
	}
	IMAGEMANAGER->frameRender("마리오",getMemDC(), _player.rc.left, _player.rc.top);
	

	for (int i = 0; i < _enemyVec.size(); i++)
	{
		if (IntersectRect(&rcTemp, &_player.rc, &_enemyVec[i]))
		{
			Sleep(1000);
			Rectangle(getMemDC(), WINSIZEX / 2 - 100, WINSIZEY / 2 - 100, WINSIZEY / 2 + 100, WINSIZEY / 2 + 100);
			TextOut(hdc, WINSIZEX/2, WINSIZEY/2, "게임 종료", strlen("게임 종료"));
			exit(0);
		}
	}
	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
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
