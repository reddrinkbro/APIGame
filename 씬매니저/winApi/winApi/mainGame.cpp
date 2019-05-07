#include "stdafx.h"
#include "mainGame.h"
#include "startScene.h"
#include "secondScene.h"
#include "thirdScene.h"
#include "endScene.h"
//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ
	SCENEMANAGER->addScene("start", new startScene);
	SCENEMANAGER->addScene("secondScene", new secondScene);
	SCENEMANAGER->addScene("thirdScene", new thirdScene);
	SCENEMANAGER->addScene("endScene", new endScene);
	SCENEMANAGER->changeScene("start");
	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���

}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	SCENEMANAGER->update();
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(void)
{
	//������ �� ��Ʈ�� (�̰͵� ������ �״�� �Ѱ�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	//=============================================================
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(getHDC());
}
