#include "stdafx.h"
#include "shootingScene.h"

HRESULT shootingScene::init(void)
{
	IMAGEMANAGER->addImage("background", "background.bmp", WINSIZEX, WINSIZEY);

	_rocket = new rocket;
	_rocket->init();

	_em = new enemyManager;
	_em->init();

	_missileEffect = new missileEffect;
	_missileEffect->init();

	_beamEffect = new beamEffect;
	_beamEffect->init();

	_em->setRocketMemoryAddress(_rocket);
	_rocket->setEnemyManagerMemoryAddress(_em);

	wsprintf(_text, "¿©±â°¡ ½´ÆÃ¾À");

	_x = _y = 0.0f;

	return S_OK;
}

void shootingScene::release(void)
{
	_rocket->release();
	SAFE_DELETE(_rocket);

	_em->release();
	SAFE_DELETE(_em);

	_missileEffect->release();
	SAFE_DELETE(_missileEffect);

	_beamEffect->release();
	SAFE_DELETE(_beamEffect);
}

void shootingScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SCENEMANAGER->changeScene("start");
	}

	_rocket->update();

	_em->update();

	collision();

	_y -= 1.0f;
}

void shootingScene::render(void)
{
	RECT rc = { 0, 0, WINSIZEX, WINSIZEY };
	IMAGEMANAGER->findImage("background")->loopRender(getMemDC(), &rc, _x, _y);

	_rocket->render();
	_em->render();
	_missileEffect->render();
	_beamEffect->render();
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, _text, strlen(_text));
}
