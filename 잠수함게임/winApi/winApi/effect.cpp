#include "stdafx.h"
#include "effect.h"

HRESULT enemyEffect::init(void)
{
	return S_OK;
}

void enemyEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void enemyEffect::update(void)
{
}

void enemyEffect::render(void)
{
	draw();
}

void enemyEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left,
			_viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 15 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
}

void enemyEffect::show(RECT rc)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));
	effect.img = new image;
	effect.img->init("enemyDie.bmp", 0.0f, 0.0f,
		525, 57, 6, 1, true, RGB(255, 0, 255));
	effect.x = rc.left + (rc.right - rc.left) / 2;
	effect.y = rc.top + (rc.bottom - rc.top) / 2;
	effect.rc = RectMakeCenter(effect.x, effect.y,
		effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vEffect.push_back(effect);
}

void enemyEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);

	_vEffect.erase(_vEffect.begin());
}

HRESULT rocketLauncherEffect::init(void)
{
	return S_OK;
}

void rocketLauncherEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void rocketLauncherEffect::update(void)
{

}

void rocketLauncherEffect::render(void)
{
	draw();
}

void rocketLauncherEffect::show(RECT rc)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));
	effect.img = new image;
	effect.img->init("enegyBallEffect.bmp", 0.0f, 0.0f,
		365, 62, 5, 1, true, RGB(77, 109, 243));
	effect.x = rc.left + (rc.right - rc.left) / 2;
	effect.y = rc.top + (rc.bottom - rc.top) / 2;
	effect.rc = RectMakeCenter(effect.x, effect.y,
		effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vEffect.push_back(effect);
}

void rocketLauncherEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left,
			_viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 5 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
}

void rocketLauncherEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);

	_vEffect.erase(_vEffect.begin());
}


HRESULT missileEffect::init(void)
{
	return S_OK;
}

void missileEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void missileEffect::update(void)
{
}

void missileEffect::render(void)
{
	draw();
}

void missileEffect::show(RECT rc)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));
	effect.img = new image;
	effect.img->init("explosion.bmp", 0.0f, 0.0f, 138, 67, 3, 1, true, RGB(84, 109, 142));
	effect.x = rc.left + (rc.right - rc.left) / 2;
	effect.y = rc.top + (rc.bottom - rc.top) / 2;
	effect.rc = RectMakeCenter(effect.x, effect.y,
		effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vEffect.push_back(effect);
}

void missileEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left,
			_viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 7 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
}

void missileEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);

	_vEffect.erase(_vEffect.begin()+ arrNum);
}


HRESULT helicopterDieEffect::init(void)
{
	return S_OK;
}

void helicopterDieEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void helicopterDieEffect::update(void)
{
}

void helicopterDieEffect::render(void)
{
	draw();
}

void helicopterDieEffect::show(RECT rc)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));
	effect.img = new image;
	effect.img->init("explosion2.bmp", 0.0f, 0.0f, 1246, 243, 5, 1, true, RGB(255, 0,255));
	effect.x = rc.left + (rc.right - rc.left) / 2;
	effect.y = rc.top + (rc.bottom - rc.top) / 2;
	effect.rc = RectMakeCenter(effect.x, effect.y,
		effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vEffect.push_back(effect);
}

void helicopterDieEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left,
			_viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 3 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
}

void helicopterDieEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);

	_vEffect.erase(_vEffect.begin() + arrNum);
}

HRESULT playerEffect::init(void)
{
	return S_OK;
}

void playerEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void playerEffect::update(void)
{
}

void playerEffect::render(void)
{
	draw();
}

void playerEffect::show(RECT rc)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));
	effect.img = new image;
	effect.img->init("playerHitEffect.bmp", 0.0f, 0.0f, 109, 17, 6, 1, true, RGB(255, 0, 255));
	effect.x = rc.left + (rc.right - rc.left) / 2;
	effect.y = rc.top + (rc.bottom - rc.top) / 2;
	effect.rc = RectMakeCenter(effect.x, effect.y,
		effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vEffect.push_back(effect);
}

void playerEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left,
			_viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 3 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
}

void playerEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);

	_vEffect.erase(_vEffect.begin() + arrNum);
}


