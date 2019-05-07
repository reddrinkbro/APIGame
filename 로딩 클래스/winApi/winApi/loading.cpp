#include "stdafx.h"
#include "loading.h"

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_0;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_1;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_2;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = maxFrameX;
	_imageResource.frameY = maxFrameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = maxFrameX;
	_imageResource.frameY = maxFrameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loading::init(void)
{
	//로딩화면 백그라운드 이미지 초기화
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "image/로딩화면.bmp", WINSIZEX, WINSIZEY);
	
	//로딩바 초기화
	_loadingBar = new progressBar;
	_loadingBar->init("barTop", "barBottom", WINSIZEX / 2 - 300, WINSIZEY / 2 + 250,
		800, 8);
	_loadingBar->setGauge(0, 0);
	
	_loadingNum._image = IMAGEMANAGER->addFrameImage("loadingNum", "숫자.bmp", 330, 35, 11, 1, true, RGB(255, 255, 255));
	_loadingNum._isShow = false;
	_vloadNum1.push_back(_loadingNum);
	_loadingNum._image = IMAGEMANAGER->addFrameImage("loadingNum1", "숫자.bmp", 330, 35, 11, 1, true, RGB(255, 255, 255));
	_loadingNum._isShow = false;
	_vloadNum10.push_back(_loadingNum);
	_loadingNum._image = IMAGEMANAGER->addFrameImage("loadingNum2", "숫자.bmp", 330, 35, 11, 1, true, RGB(255, 255, 255));
	_loadingNum._isShow = false;
	_vloadNum100.push_back(_loadingNum);
	
	_currentGauge = 0;
	return S_OK;
}

void loading::release(void)
{
	SAFE_DELETE(_loadingBar);
}

void loading::update(void)
{
	_vloadNum1[0]._isShow = true;
	_loadingBar->update();
	_count++;
	//if (_vloadNum1[0]._count + _vloadNum1[0]._count1 < TIMEMANAGER->getWorldTime())
	//{
		//_vloadNum1[0]._count = TIMEMANAGER->getWorldTime();
	if(_count % 10 == 0)
	{
		_vloadNum1[0]._image->setFrameX(_vloadNum1[0]._image->getFrameX() + 1);
		if (_vloadNum1[0]._image->getFrameX() >= _vloadNum1[0]._image->getMaxFrameX())
		{
			_vloadNum1[0]._image->setFrameX(0);
			_vloadNum10[0]._isShow = true;
			_vloadNum10[0]._image->setFrameX(_vloadNum10[0]._image->getFrameX() + 1);
			if (_vloadNum10[0]._image->getFrameX() >= _vloadNum10[0]._image->getMaxFrameX())
			{
				_vloadNum10[0]._image->setFrameX(0);
				_vloadNum100[0]._isShow = true;
				_vloadNum100[0]._image->setFrameX(1);
			}
		}
	}

}

void loading::render(void)
{
	_background->render(getMemDC());
	_loadingBar->render();
	
	if (_vloadNum1[0]._isShow)
	{
		_vloadNum1[0]._image->frameRender(getMemDC(), WINSIZEX - 60, _loadingBar->getRect().top);
	}
	if (_vloadNum10[0]._isShow)
	{
		_vloadNum10[0]._image->frameRender(getMemDC(), WINSIZEX - 90, _loadingBar->getRect().top);
	}
	if (_vloadNum100[0]._isShow)
	{
		_vloadNum100[0]._image->frameRender(getMemDC(), WINSIZEX - 120, _loadingBar->getRect().top);
	}
	
}

void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

//로딩완료 됐냐? (로딩완료후 화면 전환)
BOOL loading::loadingDone(void)
{
	//로딩이 완료 됨
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	}
	break;
	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_IMAGE_2:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_SOUND:
		break;
	}

	_currentGauge++;

	//로딩바 이미지 변경
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	return FALSE;
}
