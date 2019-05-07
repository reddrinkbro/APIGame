#include "stdafx.h"
#include "tank.h"

HRESULT tank::init(void)
{
	//탱크 방향 초기화
	_direction = TANKDIRECTION_RIGHT;

	_image = IMAGEMANAGER->addFrameImage("tank", "TileMapTank.bmp", 120, 30, 4, 1, true, RGB(255, 0, 255));
	
	_speed = 100.0f;

	return S_OK;
}

void tank::release(void)
{
}

void tank::update(void)
{
	RECT _rcTemp;
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (IntersectRect(&_rcTemp, &CollisionAreaResizing(_rc, 0, 10), &_tankMap->getTiles()[i].rc) && _tankMap->getAttribute()[i] == ATTR_UNMOVE)
		{
			count = 1;
		
			tankMove(false);
			break;
		}
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_UP) && count != 2 )
	{
		if (count == 1) count = 2;
		_direction = TANKDIRECTION_UP;
		tankMove(true);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && count != 2 )
	{
		if (count == 1) count = 2;
		_direction = TANKDIRECTION_DOWN;
		tankMove(true);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && count != 2)
	{
		if (count == 1) count = 2;
		_direction = TANKDIRECTION_LEFT;
		tankMove(true);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && count !=2)
	{
		if (count == 1) count = 2;
		_direction = TANKDIRECTION_RIGHT;
		tankMove(true);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP)) count = 0;
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN)) count = 0;
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT)) count = 0;
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) count = 0;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void tank::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}

void tank::tankMove(bool isMove)
{
	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;
	if (count == 2)
	{
		return;
	}
	if (isMove)
	{
		switch (_direction)
		{
		case TANKDIRECTION_LEFT:
			_image->setFrameX(1);
			_image->setFrameY(0);
			_x -= moveSpeed;
			break;

		case TANKDIRECTION_RIGHT:
			_image->setFrameX(2);
			_image->setFrameY(0);
			_x += moveSpeed;
			break;

		case TANKDIRECTION_UP:
			_image->setFrameX(3);
			_image->setFrameY(0);
			_y -= moveSpeed;
			break;

		case TANKDIRECTION_DOWN:
			_image->setFrameX(0);
			_image->setFrameY(0);
			_y += moveSpeed;
			break;
		}
	}
	else
	{
		switch (_direction)
		{
		case TANKDIRECTION_LEFT:
			_x += moveSpeed;
			break;

		case TANKDIRECTION_RIGHT:
			_x -= moveSpeed;
			break;

		case TANKDIRECTION_UP:
			_y += moveSpeed;
			break;

		case TANKDIRECTION_DOWN:
			_y -= moveSpeed;
			break;
		}
	}
	//_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void tank::setTankPosition()
{
	_rc = _tankMap->getTiles()[_tankMap->getPosFirst()].rc;
	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}
