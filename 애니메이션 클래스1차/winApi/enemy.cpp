#include "stdafx.h"
#include "enemy.h"

enemy::enemy() : _currentFrameX(0),
				 _currentFrameY(0),
				 _x(0.0f),
				 _y(0.0f),
				 _rc(RectMake(0, 0, 0, 0)),
				 _worldTimeCount(0.0f),
				 _rndTimeCount(0.0f)
{
}


HRESULT enemy::init(void)
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);

	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y,
		_image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{
	move();
}

void enemy::render(void)
{
	draw();
	animation();
}

//���ʹ̸��� �������� Ʋ���� ��ӹ޾� �ڽĿ��� ����
void enemy::move(void)
{
}

void enemy::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY);
}

void enemy::animation(void)
{
	//if (_rndTimeCount + _worldTimeCount <= GetTickCount())
	//{
	//	_worldTimeCount = GetTickCount();
	//	_currentFrameX++;
	//	if (_image->getMaxFrameX() < _currentFrameX)
	//	{
	//		_currentFrameX = 0;
	//	}
	//}

	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}
}
