#include "stdafx.h"
#include "animationTest.h"


HRESULT animationTest::init(void)
{
	gameNode::init();

	_image = IMAGEMANAGER->addImage("elephant", "elephant.bmp", 660, 268, true, RGB(255, 0, 255));

	_animation0 = new animation;
	_animation0->init(_image->getWidth(), _image->getHeight(), 110, 67);
	_animation0->setDefPlayFrame(false, true);
	_animation0->setFPS(12);
	for (int i = 0; i < 5; i++)
	{
		arr[i] = RND->getInt(20);
	}
	count = 0;
	return S_OK;
}

void animationTest::release(void)
{
	_animation0->release();
	SAFE_DELETE(_animation0);
}

void animationTest::update(void)
{
	if (KEYMANAGER->isToggleKey('B'))
	{
		if (count == 0)
		{
			parr = arr;
			_animation0->setPlayFrame(parr, 5, true);
			*parr++;
			count++;
		}
		else if (count == 5)
		{
			_animation0->setPlayFrame(parr, 5, true);
		}
		else
		{
			_animation0->setPlayFrame(parr, 5, true);
			*parr++;
			count++;
		}
		
		//_animation0->setPlayFrame(2, 2, true);
		//_animation0->start();
		Sleep(1000);
	}
	//_animation0->frameUpdate(TIMEMANAGER->getElapsedTime() * 0.01);
	//_animation0->isPlay();
}

void animationTest::render(void)
{
	char str[128];
	sprintf_s(str, "%d %d", _animation0->getFrameIdx(), _animation0->getNowPlayIdx());
	TextOut(getMemDC(), 100, WINSIZEY - 100, str, strlen(str));
	_image->aniRender(getMemDC(), WINSIZEX / 2 - 50, WINSIZEY / 2, _animation0);
}

