#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화

	IMAGEMANAGER->addImage("background", "background.bmp", WINSIZEX, WINSIZEY);
	
	_rocket = new rocket;
	_rocket->init();
	
	_em = new enemyManager;
	_em->init();

	_enemyEffect = new enemyEffect;
	_enemyEffect->init();

	_enemyEnegyBallEffect = new enemyEnegyBallEffect;
	_enemyEnegyBallEffect->init();

	_bossHitEffect = new bossHitEffect;
	_bossHitEffect->init();

	_bossDieEffect = new bossDieEffect;
	_bossDieEffect->init();

	_playerEffect = new playerEffect;
	_playerEffect->init();

	_objectWind = new objectWind;
	_objectWind->init();

	_startScene = new startScene;
	_startScene->init();

	_secondScene = new secondScene;
	_secondScene->init();

	_gameEndScene = new gameEndScene;
	_gameEndScene->init();

	_currentScean = _startScene;

	_sceanNum = 0;
	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용

	_rocket->release();
	SAFE_DELETE(_rocket);

	_em->release();
	SAFE_DELETE(_em);

	_enemyEffect->release();
	SAFE_DELETE(_enemyEffect);

	_enemyEnegyBallEffect->release();
	SAFE_DELETE(_enemyEnegyBallEffect);

	_bossHitEffect->release();
	SAFE_DELETE(_bossHitEffect);

	_bossDieEffect->release();
	SAFE_DELETE(_bossDieEffect);

	_playerEffect->release();
	SAFE_DELETE(_playerEffect);

	_objectWind->release();
	SAFE_DELETE(_objectWind);

	_startScene->release();
	SAFE_DELETE(_startScene);

	_secondScene->release();
	SAFE_DELETE(_secondScene);

	_gameEndScene->release();
	SAFE_DELETE(_gameEndScene);
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();

	_currentScean->update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_currentScean = _secondScene;
		_sceanNum = 1;
	}

	if (_sceanNum == 1)
	{
		_rocket->update();

		_objectWind->update();

		_em->update();

		collision();

		enemyMissileDirection();

		showBoss();
	}
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(void)
{
	//검은색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================

	_currentScean->render();
	if (_sceanNum == 1)
	{
		_rocket->render();

		_em->render();

		_enemyEffect->render();

		_enemyEnegyBallEffect->render();

		_bossHitEffect->render();

		_bossDieEffect->render();

		_playerEffect->render();

		_objectWind->render();
	}
	TIMEMANAGER->render(getMemDC());

	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(getHDC());
}
