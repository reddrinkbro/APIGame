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
	_bgImage->init("배경.bmp", WINSIZEX, WINSIZEY-100);

	_fieldImage = new image;
	_fieldImage->init("field.bmp", WINSIZEX, 100, true, RGB(255, 0, 255));

	_objectImage = new image;
	_objectImage->init("object.bmp", 100, 170, true, RGB(255, 0, 255));

	//프레임 이미지 초기화
	_mario = new image;
	_mario->init("mario.bmp", WINSIZEX/2 ,WINSIZEY /2 , 66, 84, 3, 4, true, RGB(255, 0, 255));
	
	_isLeft = false;

	_player.rc = RectMake(0, WINSIZEY - 120, 20, 20);
	field = RectMake(0, WINSIZEY - 100, WINSIZEX, WINSIZEY);
	object = RectMake(WINSIZEX/2, WINSIZEY - 270, 100 , WINSIZEY - 100);
	_player.bulletAngle = PI / 2;
	_player.time = 0;
	_player.isJump = false;
	_player.isClimbing = false;
	_isMove = false;
	_player.gravity = 9.8f;
	_isClimb = false;
	finishTime = 2;
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
	SAFE_DELETE(_fieldImage);
	SAFE_DELETE(_objectImage);
	SAFE_DELETE(_mario);
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	jumpAfterRect();
	intersect();
	RECT rcTemp;
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	/*if (field.top > _player.rc.bottom) // 항상 바닥으로 이동한다 중력같은거
	{
		_player.rc.top += 3;
		_player.rc.bottom += 3;
	}*/
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		_isMove = true;
		if (_isMove && !_isClimb)
		{
			_player.rc.left += 3;
			_player.rc.right += 3;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_player.rc.right > object.right && _isClimb)
		{
			_player.rc.left += 10;
			_player.rc.right += 10;
		}
		_isClimb = false;
	}
	if(KEYMANAGER->isOnceKeyUp(VK_RIGHT))_isMove = false;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player.rc.left > 0)
	{
		_isMove = true;
		_isLeft = true;
		if (_isMove && !_isClimb)
		{
			_player.rc.left -= 3;
			_player.rc.right -= 3;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_player.rc.left < object.left && _isClimb)
		{
			_player.rc.left -= 10;
			_player.rc.right -= 10;
		}
		_isClimb = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))_isMove = false;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _isClimb)
	{
		_player.isJump = false;
		_player.rc.top += 3;
		_player.rc.bottom += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _isClimb )
	{
		_player.isJump = false;
		_player.rc.top -= 3;
		_player.rc.bottom -= 3;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_player.isJump = true;
	}
	if (IntersectRect(&rcTemp, &_player.rc, &object))
	{
		_player.isClimbing = true;
	}
	if (_player.isJump) // 점프할때
	{
		_player.time += 0.03;
		if (!_isClimb)
		{
			jump();
		}
		if (_isLeft)
		{
			_mario->setFrameY(2);
			_mario->setFrameX(3);
		}
		else 
		{
			_mario->setFrameY(3);
			_mario->setFrameX(0);
		}
	}
	if (_isMove && !_player.isJump) // 이동프레임
	{
		//왼쪽프레임 일때 애니메이션 Start
		if (!_isLeft)
		{
			_count++;
			_mario->setFrameY(0);
			//애니메이션 속도
			if (_count % 6 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 2;
				}
				_mario->setFrameX(_index);
			}
		}
		else
		{
			_count++;
			_mario->setFrameY(1);
			if (_count % 6 == 0)
			{
				_index++;
				if (_index > 3)
				{
					_index = 0;
				}
				_mario->setFrameX(_index);
			}
		}
	}
	else if (!_isMove && !_player.isJump) // 대기상태 프레임
	{
		_mario->setFrameY(3);
		if (!_isLeft)
		{
			_mario->setFrameX(2);
		}
		else
		{
			_mario->setFrameX(3);
		}
	}
	if (_isClimb) //기어오르는상태 프레임
	{
		_player.isJump = false;
		_player.time = 0;
		_mario->setFrameY(2);
		if (_isLeft)
		{
			_mario->setFrameX(1);
		}
		else
		{
			_mario->setFrameX(0);
		}
		if (_player.rc.bottom > object.top && _player.rc.bottom < object.top + 15)
		{
			_player.rc.bottom = object.top;
			_player.rc.top = _player.rc.bottom - 20;
		}
	}
	if (_player.isClimbing)
	{
		_player.time = 0;
		_isClimb = false;
		_player.isJump = false;
	}
	else
	{
		_player.rc.top += 3;
		_player.rc.bottom += 3;
	}
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	//백버퍼 가져오기 (이건 렌더에 그대로 둘것)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//흰색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	RECT rcTemp;
	_bgImage->render(memDC);
	sprintf(str, "%d %d", _player.rc.bottom, object.top); 
	TextOut(memDC, 0, 0, str, strlen(str));
	_objectImage->render(memDC, object.left, object.top);
	_fieldImage->render(memDC, field.left, field.top);
	_mario->frameRender(memDC, _player.rc.left, _player.rc.top);
	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(hdc);
}
void mainGame::jump(void)
{
	RECT rcTemp;
	/*if (_player.time > finishTime)
	{
		_player.gravity -= 9.8f / 100;
		_player.rc.left = cosf(_player.bulletAngle) * 5 + _player.rc.left;
		_player.rc.right = cosf(_player.bulletAngle) * 5 + _player.rc.right;
		_player.rc.bottom = sinf(_player.bulletAngle) * 5 - (_player.gravity*_player.time) + _player.rc.bottom;
		_player.rc.top = sinf(_player.bulletAngle) * 5 - (_player.gravity*_player.time) + _player.rc.top;
		
		//_player.isClimbing = false;
	}
	else
	{*/
		_player.rc.left = cosf(_player.bulletAngle) * 8 + _player.rc.left;
		_player.rc.right = cosf(_player.bulletAngle) * 8 + _player.rc.right;
		if (_player.isClimbing)
		{
			_player.rc.bottom = -(sinf(_player.bulletAngle) * 5 - (_player.gravity*_player.time)) + _player.rc.bottom;
			_player.rc.top = -(sinf(_player.bulletAngle) * 5 - (_player.gravity*_player.time)) + _player.rc.top;
		}
		else
		{
			_player.rc.bottom = -(sinf(_player.bulletAngle) * 8 - (_player.gravity*_player.time)) + _player.rc.bottom;
			_player.rc.top = -(sinf(_player.bulletAngle) * 8 - (_player.gravity*_player.time)) + _player.rc.top;
		}
		_player.isClimbing = false;
		
	//}
	
}

void mainGame::jumpAfterRect(void)
{
	RECT rcTemp;
	if (_player.rc.right > object.left && _player.rc.left < object.right)
	{
		if (_player.rc.bottom <= object.top + 5)
		{
			_isClimb = false;
		}
		else 
		{
			_isClimb = true;
		}
	}
	else
	{
		_player.isClimbing = false; // 장애물 위쪽에서 벗어나면 다시 떨어져야하기 때문에
		_isClimb = false;
	}
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
	}
}
