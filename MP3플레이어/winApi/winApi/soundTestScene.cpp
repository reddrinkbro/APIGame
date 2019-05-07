#include "stdafx.h"
#include "soundTestScene.h"

HRESULT soundTestScene::init(void)
{
	_num = 0;
	IMAGEMANAGER->addImage("1", "1.bmp", WINSIZEX, WINSIZEY - 65);
	IMAGEMANAGER->addImage("2", "2.bmp", WINSIZEX, WINSIZEY - 65);
	IMAGEMANAGER->addImage("3", "3.bmp", WINSIZEX, WINSIZEY - 65);
	IMAGEMANAGER->addImage("4", "4.bmp", WINSIZEX, WINSIZEY - 65);
	IMAGEMANAGER->addImage("5", "5.bmp", WINSIZEX, WINSIZEY - 65);
	IMAGEMANAGER->addImage("6", "6.bmp", WINSIZEX, WINSIZEY - 65);
	IMAGEMANAGER->addImage("7", "7.bmp", WINSIZEX, WINSIZEY - 65);
	IMAGEMANAGER->addImage("mp3bar", "mp3바.bmp", WINSIZEX, 65);
	IMAGEMANAGER->addImage("play", "play.bmp", 34, 65);
	IMAGEMANAGER->addImage("2", "2.bmp", WINSIZEX, WINSIZEY - 65);
	SOUNDMANAGER->addSound("1", "1.mp3", true, true);
	SOUNDMANAGER->addSound("2", "2.mp3", true, true);
	SOUNDMANAGER->addSound("3", "3.mp3", true, true);
	SOUNDMANAGER->addSound("4", "4.mp3", true, true);
	SOUNDMANAGER->addSound("5", "5.mp3", true, true);
	SOUNDMANAGER->addSound("6", "6.mp3", true, true);
	SOUNDMANAGER->addSound("7", "7.mp3", true, true);
	_rc[0] = RectMakeCenter(1000, WINSIZEY-33, 30, 65);
	_rc[1] = RectMakeCenter(1050, WINSIZEY - 33, 30, 65);
	_rc[2] = RectMakeCenter(1100, WINSIZEY - 33, 30, 65);
	
	_progressBar = new progressBar;
	_progressBar->init("barTop", "barBottom", 350,WINSIZEY - 40,518,6);
	_rc[3] = RectMakeCenter(610, WINSIZEY - 35, 518, 30);
	_volumeBar = new progressBar;
	_volumeBar->init("volumeTop", "volumeBottom", 1150, WINSIZEY - 35, 116, 4);
	_rc[4] = RectMakeCenter(1208, WINSIZEY - 30, 116, 8);
	return S_OK;
}

void soundTestScene::release(void)
{
	_progressBar->release();
	SAFE_DELETE(_progressBar);
}

void soundTestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (SOUNDMANAGER->isPauseSound(SOUNDMANAGER->getSoundName()[_num]))
		{
			resume();
		}
		else if (!SOUNDMANAGER->isPlaySound(SOUNDMANAGER->getSoundName()[_num]))
		{
			play();
			
		}
		else if(!SOUNDMANAGER->isPauseSound(SOUNDMANAGER->getSoundName()[_num]))
		{
			pause();
		}
		next();
		previous();
		setPosition();
		setVolume();
	}
	soundChange();
	SOUNDMANAGER->update();
	_progressBar->update();
	_progressBar->setGauge(SOUNDMANAGER->soundPosition(SOUNDMANAGER->getSoundName()[_num]), SOUNDMANAGER->soundLength(SOUNDMANAGER->getSoundName()[_num]));
	_volumeBar->update();
	_volumeBar->setGauge(SOUNDMANAGER->getVolume(SOUNDMANAGER->getSoundName()[_num]), 1);
	
}

void soundTestScene::render(void)
{
	IMAGEMANAGER->render(SOUNDMANAGER->getSoundName()[_num], getMemDC());
	IMAGEMANAGER->render("mp3bar", getMemDC(),0,WINSIZEY-65);
	_progressBar->render();
	_volumeBar->render();
	if (!SOUNDMANAGER->isPlaySound(SOUNDMANAGER->getSoundName()[_num]) || SOUNDMANAGER->isPauseSound(SOUNDMANAGER->getSoundName()[_num]))
	{
		IMAGEMANAGER->render("play", getMemDC(), 1035, WINSIZEY - 65);
	}
	char str[128];
	sprintf(str, "%02d : %02d", SOUNDMANAGER->soundPosition(SOUNDMANAGER->getSoundName()[_num]) / 1000 / 60, SOUNDMANAGER->soundPosition(SOUNDMANAGER->getSoundName()[_num]) /1000 % 60);
	TextOut(getMemDC(), 280, WINSIZEY - 40, str, strlen(str));
	sprintf(str, "%02d : %02d", SOUNDMANAGER->soundLength(SOUNDMANAGER->getSoundName()[_num])/1000 / 60, SOUNDMANAGER->soundLength(SOUNDMANAGER->getSoundName()[_num]) / 1000 % 60);
	TextOut(getMemDC(), 900, WINSIZEY - 40, str, strlen(str));
}
//재생
void soundTestScene::play(void)
{
	if (PtInRect(&_rc[1], _ptMouse))
	{
		SOUNDMANAGER->play(SOUNDMANAGER->getSoundName()[_num],0.2f);
	}
}
//일시정지
void soundTestScene::pause(void)
{
	if (PtInRect(&_rc[1], _ptMouse))
	{
		SOUNDMANAGER->pause(SOUNDMANAGER->getSoundName()[_num]);
	}
}
//재개
void soundTestScene::resume(void)
{
	if (PtInRect(&_rc[1], _ptMouse))
	{
		SOUNDMANAGER->resume(SOUNDMANAGER->getSoundName()[_num]);
	}
}
//다음 곡
void soundTestScene::next(void)
{
	if (PtInRect(&_rc[2], _ptMouse))
	{
		if (SOUNDMANAGER->getSoundName().size() - 1 > _num)
		{
			_num++;
		}
		else 
		{
			_num = 0;
		}
		SOUNDMANAGER->next();
	}	
}
//이전 곡
void soundTestScene::previous(void)
{

	if (PtInRect(&_rc[0], _ptMouse))
	{
		if (_num > 0)
		{
			_num--;
		}
		else
		{
			_num = SOUNDMANAGER->getSoundName().size() -1;
		}
		SOUNDMANAGER->previous();
	}
}
//재생위치 조절
void soundTestScene::setPosition(void)
{
	float percent =  SOUNDMANAGER->soundLength(SOUNDMANAGER->getSoundName()[_num]) / (_rc[3].right - _rc[3].left) ;
	if (PtInRect(&_rc[3], _ptMouse))
	{
		SOUNDMANAGER->soundSetPosition(SOUNDMANAGER->getSoundName()[_num],(_ptMouse.x - _rc[3].left) * percent);
	}
}
//볼륨 조절
void soundTestScene::setVolume(void)
{
	float percent = _rc[4].right - _rc[4].left;
	if (PtInRect(&_rc[4], _ptMouse))
	{
		SOUNDMANAGER->setVolume(SOUNDMANAGER->getSoundName()[_num],(_ptMouse.x-_rc[4].left)/percent);
	}
}

void soundTestScene::soundChange(void)
{
	
	if(SOUNDMANAGER->soundPosition(SOUNDMANAGER->getSoundName()[_num]) + 50 >= SOUNDMANAGER->soundLength(SOUNDMANAGER->getSoundName()[_num]))
	{ 
		if (SOUNDMANAGER->getSoundName().size() - 1 > _num)
		{
			_num++;
		}
		else
		{
			_num = 0;
		}
		SOUNDMANAGER->next();
	}
}
