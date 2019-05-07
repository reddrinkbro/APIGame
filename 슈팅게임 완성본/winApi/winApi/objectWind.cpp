#include "stdafx.h"
#include "objectWind.h"


HRESULT objectWind::init(void)
{
	_image = IMAGEMANAGER->addFrameImage("wind", "wind.bmp", 0.0f, 0.0f, 256, 80, 4, 1, true, RGB(255, 0, 255));
	for (int i = 0; i < 2; i++)
	{
		_rc = RectMakeCenter(RND->getInt(WINSIZEX), -RND->getInt(WINSIZEY), _image->getFrameWidth(), _image->getFrameHeight());
		_vRect.push_back(_rc);
	}
	_count = 0;
	return S_OK;
}

void objectWind::release(void)
{
}

void objectWind::update(void)
{
	_count++;
	for(_viRect = _vRect.begin(); _viRect != _vRect.end(); ++_viRect)
	{
		_viRect->top += 5;
		_viRect->bottom += 5;

		if (_viRect->top > WINSIZEY)
		{
			_viRect->left = RND->getInt(WINSIZEX);
			_viRect->right = _viRect->left + _image->getFrameWidth();
			_viRect->top = -RND->getInt(WINSIZEY);  
			_viRect->bottom = _viRect->top + _image->getFrameHeight();
		}
	}
	if (_count % 6==0)
	{
		_image->setFrameX(_image->getFrameX() + 1);
		if (_image->getFrameX() >= _image->getMaxFrameX())
		{
			_image->setFrameX(0);
		}
	}
}

void objectWind::render(void)
{
	for (_viRect = _vRect.begin(); _viRect != _vRect.end(); ++_viRect)
	{
		_image->frameRender(getMemDC(), _viRect->left, _viRect->top);
	}
}
