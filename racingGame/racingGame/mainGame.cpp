#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화
	IMAGEMANAGER->addImage("플레이어", "플레이어.bmp", 43, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("적", "적.bmp", 43, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경", "도로.bmp", 255, 2400);
	IMAGEMANAGER->addImage("계기판", "계기판.bmp", 150, 130);
	IMAGEMANAGER->addImage("화살표", "화살표.bmp", 18, 62, true, RGB(255, 0, 255));
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
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	
	_bgSpeed -= _speed;
	_enemy = RectMake(RND->getFromIntTo(WINSIZEX / 2 - 112, WINSIZEX / 2 + 112), -RND->getFromIntTo(0, 2 * WINSIZEY) ,43, 83);
	_arrow.end.x = cosf(_arrow.angle) * _arrow.length + _arrow.start.x;
	_arrow.end.y = -sinf(_arrow.angle) * _arrow.length + _arrow.start.y;
	enemyCreate();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다		
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
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
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	RECT rcTemp;
	HPEN Brush;
	//흰색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	Rectangle(getMemDC(),0 ,0 , WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("배경", getMemDC(), &RectMake(WINSIZEX / 2 - 112, 0, 255, WINSIZEY), 0, _bgSpeed);
	IMAGEMANAGER->render("계기판", getMemDC(), 0, WINSIZEY - 130);
	LineMake(getMemDC(), _arrow.start.x, _arrow.start.y, _arrow.end.x, _arrow.end.y);
	sprintf(str, "현재 점수 : %d", _score);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
	
	for (int i = 0; i < _enemyVec.size(); i++)
	{
		IMAGEMANAGER->render("적", getMemDC(), _enemyVec[i].left, _enemyVec[i].top);
	}

	IMAGEMANAGER->render("플레이어",getMemDC(), _player.left, _player.top);
	
	for (int i = 0; i < _enemyVec.size(); i++)
	{
		/*if (IntersectRect(&rcTemp, &_player, &_enemyVec[i]))
		{
			Sleep(1000);
			Rectangle(getMemDC(), WINSIZEX / 2 - 100, WINSIZEY / 2 - 100, WINSIZEY / 2 + 100, WINSIZEY / 2 + 100);
			TextOut(hdc, WINSIZEX/2, WINSIZEY/2, "게임 종료", strlen("게임 종료"));
			exit(0);
		}*/
	}
	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
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
