#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ

	IMAGEMANAGER->addImage("background", "background.bmp", WINSIZEX, WINSIZEY);
	rc = RectMakeCenter(WINSIZEX/2,50, WINSIZEX, WINSIZEY/2 + 100);
	_rocket = new rocket;
	_rocket->init();
	
	_em = new enemyManager;
	_em->init();

	_enemyEffect = new enemyEffect;
	_enemyEffect->init();

	_rocketLauncherEffect = new rocketLauncherEffect;
	_rocketLauncherEffect->init();

	_missileEffect = new missileEffect;
	_missileEffect->init();

	_helicopterDieEffect = new helicopterDieEffect;
	_helicopterDieEffect->init();


	_playerEffect = new playerEffect;
	_playerEffect->init();

	_startScene = new startScene;
	_startScene->init();

	_secondScene = new secondScene;
	_secondScene->init();

	_gameEndScene = new gameEndScene;
	_gameEndScene->init();

	_currentScean = _secondScene;

	_sceanNum = 0;
	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���

	_rocket->release();
	SAFE_DELETE(_rocket);

	_em->release();
	SAFE_DELETE(_em);

	_enemyEffect->release();
	SAFE_DELETE(_enemyEffect);

	_rocketLauncherEffect->release();
	SAFE_DELETE(_rocketLauncherEffect);

	_missileEffect->release();
	SAFE_DELETE(_missileEffect);

	_helicopterDieEffect->release();
	SAFE_DELETE(_helicopterDieEffect);

	
	_playerEffect->release();
	SAFE_DELETE(_playerEffect);

	_startScene->release();
	SAFE_DELETE(_startScene);

	_secondScene->release();
	SAFE_DELETE(_secondScene);

	_gameEndScene->release();
	SAFE_DELETE(_gameEndScene);
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();

	_currentScean->update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	if (_currentScean == _secondScene)
	{
		_rocket->update();

		_em->update();

		collision();

		enemyMissileDirection();
	}
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(void)
{
	//������ �� ��Ʈ�� (�̰͵� ������ �״�� �Ѱ�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================

	_currentScean->render();
	if (_currentScean == _secondScene)
	{
		_rocket->render();

		_em->render();

		_enemyEffect->render();

		_rocketLauncherEffect->render();

		_missileEffect->render();

		_helicopterDieEffect->render();

		_playerEffect->render();
	}
	TIMEMANAGER->render(getMemDC());

	//=============================================================
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(getHDC());
}
