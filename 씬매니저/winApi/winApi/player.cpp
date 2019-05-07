#include "stdafx.h"
#include "player.h"

HRESULT player::init(float* x, float* y)
{
	_pSaveLoad = TXTMANAGER->load("player.txt");
	_image = IMAGEMANAGER->addImage("player", "Spikeball.bmp", 462, 72, true, RGB(255, 0, 255));
	_x = x;// WINSIZEX / 2;
	_y = y;
	_rc = RectMakeCenter((int)_x, (int)_y, 66, 72);
	_currentHp = atof(_pSaveLoad[0].c_str());
	_maxHp = atof(_pSaveLoad[1].c_str());
	_money = atof(_pSaveLoad[2].c_str());
	_speed = atof(_pSaveLoad[3].c_str());
	_def = 3;// atof(_pSaveLoad[6].c_str());
	_progressBar = new progressBar;
	_progressBar->init(50,100,126,15);

	_itemWindow = new itemWindow;
	_itemWindow->init();

	_animation = new animation;
	_animation->init(_image->getWidth(), _image->getHeight(), 66, 72);
	_animation->setDefPlayFrame(false, true);
	_animation->setFPS(12);

	_itemManager = new itemManager;
	_itemManager->init();

	_isShowProgressBar = false;
	return S_OK;
}

void player::release(void)
{
	_progressBar->release();
	SAFE_DELETE(_progressBar);
	_animation->release();
	SAFE_DELETE(_animation);
	_itemWindow->release();
	SAFE_DELETE(_itemWindow);
	_itemManager->release();
	SAFE_DELETE(_itemManager);
}

void player::update(void)
{
	if(KEYMANAGER->isOnceKeyDown('1'))
	{
		_currentHp--;
	}
	if (KEYMANAGER->isOnceKeyDown('2') && !_itemWindow->gethpVec().empty())
	{
		_itemWindow->usingItem(0);
		_currentHp++;
		if (_currentHp > _maxHp) _currentHp = _maxHp;
	}
	if (KEYMANAGER->isOnceKeyDown('3') && !_itemWindow->getSVec().empty())
	{
		_itemWindow->usingItem(1);
		_speed++;
		if (_speed > 5) _speed = 5;
	}
	if (KEYMANAGER->isOnceKeyDown('4') && !_itemWindow->getSwordVec().empty())
	{
		_itemWindow->usingItem(2);
		_def+=14;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT)) { _animation->start(); }
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT)) { _animation->stop(); }
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && *_x > 33) { *_x-= _speed * 2; }
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) { *_x+= _speed * 2; }

	_rc = RectMakeCenter(*_x, *_y, _image->getWidth() /7, _image->getHeight());
	_animation->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_itemWindow->update();
	_progressBar->setX(_rc.left - 33);
	_progressBar->setY(_rc.top - 15);
	_progressBar->update();
	_progressBar->setGuage(_currentHp,_maxHp);
}

void player::render(void)
{
	char str[128];
	if (_isShowProgressBar)
	{
		_progressBar->render();
	}
	_image->aniRender(getMemDC(), _rc.left, _rc.top,_animation);
	_itemWindow->render();
}

void player::save(bool save)
{
	if (save)
	{
		char str[128];
		sprintf(str, "%f, %f, %f, %f, %d, %f, %f,",_x,_y,_currentHp,_maxHp,_money,_speed,_def);
		_pSaveLoad.clear();
		_pSaveLoad.push_back(str);
		TXTMANAGER->save("player.txt", _pSaveLoad);
	}
}

void player::showProgressBar(float guage)
{
	_isShowProgressBar = true;
	_currentHp-=guage;
}
