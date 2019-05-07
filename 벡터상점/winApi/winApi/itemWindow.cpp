#include "stdafx.h"
#include "itemWindow.h"

HRESULT itemWindow::init(void)
{
	_image = IMAGEMANAGER->addImage("itemWindow", "itemWindow.bmp", 169, 195, true, RGB(255, 0, 255));
	_x = WINSIZEX - _image->getWidth() / 2;
	_y = WINSIZEY / 2 ;
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_showInventory = false;
	_openCloseinventoryCount = 0;
	for (int i = 0; i < 2; i++)
	{
		_itemPointX[i]= 0;
		_itemPointY[i]= 0;
	}
	_itemManager = new itemManager;
	_itemManager->init();
	return S_OK;
}

void itemWindow::release(void)
{
	_itemManager->release();
	SAFE_DELETE(_itemManager);
}

void itemWindow::update(void)
{
	showInventory();
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	for (int i = 0; i < 2; i++)
	{
		_itemPointX[i] = _rc.left + 26 + i * 39;
		_itemPointY[i] = _rc.top + 60;
	}
}
void itemWindow::render(void)
{
	char str[128];
	sprintf(str, "%d", _vHpItem.size());
	if (_showInventory && _openCloseinventoryCount == 1)
	{
		_image->render(getMemDC(), _rc.left, _rc.top);
		for (_viHpItem = _vHpItem.begin(); _viHpItem != _vHpItem.end(); ++_viHpItem)
		{
			(*_viHpItem)->render();
		}
		if (_vHpItem.size() > 0)
		{
			TextOut(getMemDC(), _itemPointX[0], _itemPointY[0], str, strlen(str));
		}
		sprintf(str, "%d", _vSItem.size());
		for (_viSItem = _vSItem.begin(); _viSItem != _vSItem.end(); ++_viSItem)
		{
			(*_viSItem)->render();
		}
		if (_vSItem.size() > 0)
		{
			TextOut(getMemDC(), _itemPointX[1], _itemPointY[1], str, strlen(str));
		}
	}
	
}

void itemWindow::usingItem(int num)
{
	if (hp == num)
	{
		_vHpItem.erase(_vHpItem.begin());
	}
	else if (speed == num)
	{
		_vSItem.erase(_vSItem.begin());
	}
}

void itemWindow::showInventory(void)
{
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		_showInventory = true;
		_openCloseinventoryCount++;
	}
	if (_openCloseinventoryCount > 1)
	{
		_openCloseinventoryCount = 0;
	}
}

void itemWindow::pushPotion(int num)
{
	if (hp == num)
	{
		_itemManager->gethpPotion()->setPotion(&_itemPointX[0], &_itemPointY[0]);
		_vHpItem.push_back(_itemManager->gethpPotion());
	}
	else if (speed == num)
	{
		_itemManager->getSpeedPotion()->setPotion(&_itemPointX[1], &_itemPointY[1]);
		_vSItem.push_back(_itemManager->getSpeedPotion());
	}
}

