#include "stdafx.h"
#include "pixelCollision.h"

HRESULT pixelCollision::init(void)
{
	_playerTank = new playerTank;
	_playerTank->init();
	_effect = new missileEffect;
	_effect->init();
	return S_OK;
}

void pixelCollision::release(void)
{
	_playerTank->release();
	SAFE_DELETE(_playerTank);
	_effect->release();
	SAFE_DELETE(_effect);
}

void pixelCollision::update(void)
{
	
	_playerTank->update();
	collision();
	//y축으로 탐지
	
}

void pixelCollision::render(void)
{
	for (int i = 0; i < _playerTank->getMissile()->getbullet().size(); i++)
	{
		//Rectangle(getMemDC(), _playerTank->getMissile()->getbullet()[i]._);
		Rectangle(getMemDC(), _playerTank->getMissile()->getbullet()[i]._x, _playerTank->getMissile()->getbullet()[i]._probeY, _playerTank->getMissile()->getbullet()[i]._x+10, _playerTank->getMissile()->getbullet()[i]._probeY + 10);
	}
	_effect->render();
	_playerTank->render();
}

void pixelCollision::collision(void)
{
	for (int i = 0; i < _playerTank->getMissile()->getbullet().size(); i++)
	{
		_playerTank->getMissile()->getbullet()[i]._probeY = _playerTank->getMissile()->getbullet()[i]._y + _playerTank->getMissile()->getbullet()[i]._image->getHeight() / 2;

		
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("mountain")->getMemDC(), _playerTank->getMissile()->getbullet()[i]._x, _playerTank->getMissile()->getbullet()[i]._y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_effect->show(_playerTank->getMissile()->getbullet()[i]._rc);
			_playerTank->getMissile()->remove(i);
			break;
		}
		
	}
}

void pixelCollision::pixel(void)
{
	
}
