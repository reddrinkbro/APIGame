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
		if (_viEffect->count % 8 == 0)
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
		404, 56, 6, 1, true, RGB(255, 0, 255));
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

HRESULT enemyEnegyBallEffect::init(void)
{
	return S_OK;
}

void enemyEnegyBallEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void enemyEnegyBallEffect::update(void)
{

}

void enemyEnegyBallEffect::render(void)
{
	draw();
}

void enemyEnegyBallEffect::show(RECT rc)
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

void enemyEnegyBallEffect::draw(void)
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

void enemyEnegyBallEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);

	_vEffect.erase(_vEffect.begin());
}


HRESULT bossHitEffect::init(void)
{
	return S_OK;
}

void bossHitEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void bossHitEffect::update(void)
{
}

void bossHitEffect::render(void)
{
	draw();
}

void bossHitEffect::show(RECT rc)
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

void bossHitEffect::draw(void)
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

void bossHitEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);

	_vEffect.erase(_vEffect.begin()+ arrNum);
}


HRESULT bossDieEffect::init(void)
{
	return S_OK;
}

void bossDieEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void bossDieEffect::update(void)
{
}

void bossDieEffect::render(void)
{
	draw();
}

void bossDieEffect::show(RECT rc)
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

void bossDieEffect::draw(void)
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

void bossDieEffect::removeEffect(int arrNum)
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

