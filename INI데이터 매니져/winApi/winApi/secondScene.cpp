#include "stdafx.h"
#include "secondScene.h"

HRESULT secondScene::init(player* player)
{
	IMAGEMANAGER->addImage("����", "shop.bmp", WINSIZEX, WINSIZEY);
	_portal = RectMake(WINSIZEX / 2 - 110, WINSIZEY / 2 + 75, 70, 72);

	_image = IMAGEMANAGER->addImage("shopWindow", "itemShop.bmp", 512, 117, true, RGB(255, 0, 255));
	_point[0].x = WINSIZEX / 2 - _image->getWidth() / 2 + 7;
	_point[0].y = WINSIZEY - 150 + 21;
	_point[1].x = WINSIZEX / 2 - _image->getWidth() / 2 + 44;
	_point[1].y = WINSIZEY - 150 + 21;
	_point[2].x = WINSIZEX / 2 - _image->getWidth() / 2 + 81;
	_point[2].y = WINSIZEY - 150 + 21;
	for (int i = 0; i < 3; i++)
	{
		_rc[i] = RectMake(_point[i].x, _point[i].y, 28, 28);
	}

	_showItem = false;

	_buccanary = new buccanary;
	_buccanary->init();

	_player = player;

	_itemManager = new itemManager;
	_itemManager->init();
	_sVec[0] = TXTMANAGER->load("hpPotion.txt");
	_sVec[1] = TXTMANAGER->load("speedPotion.txt");
	_sVec[2] = TXTMANAGER->load("sword.txt");

	_renderValue = INIDATA->loadDataIntrger("option", "mapLight", "key");
	return S_OK;
}

void secondScene::release(void)
{
	_buccanary->release();
	SAFE_DELETE(_buccanary);

	_itemManager->release();
	SAFE_DELETE(_itemManager);
}

void secondScene::update(void)
{
	_buccanary->update();
	_player->update();
	_itemManager->update();
	showItem();
}

void secondScene::render(void)
{
	IMAGEMANAGER->alphaRender("����", getMemDC(), _renderValue);
	_itemManager->render();
	_buccanary->render();
	if (_showItem)
	{
		_image->render(getMemDC(), WINSIZEX / 2 - _image->getWidth() / 2, WINSIZEY - 150);
	}
	_player->render();
	showText();
	/*
	//IMAGEMANAGER->loopRender("���ȭ��", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _bgSpeed, 0);
	
	//�����ϰ� �ϴ� ������ ���� �ڷ� ����� ���̰� �Ѵ�
	SetBkMode(getMemDC(), TRANSPARENT);
	//���� �ؽ�Ʈ
	char str[128];
	wsprintf(str, "������ ��Ʈ");
	TextOut(getMemDC(), 230, 250, str, strlen(str));

	//���ο� ���
	HFONT font;
	HFONT oldFont;

	//font = CreateFont
	//(
	//����ũ��, ������, ������ü����, ���ڹ���, ���ڱ���,
	//����(true, false), ����(�Ҳ���, ������), ��Ҽ�(),
	//���ڼ���, �����Ȯ��, Ŭ������Ȯ��, �������, �ڰ�, ��Ʈ
	//)
	//�������� ����ũ�⿡���� ����ϴ� 0���� �ΰ� �մ��� ����
	font = CreateFont(70, 0, 0, 0, 600,
		0, 0, 1,
		HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�޸ձ���"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	wsprintf(str, "���ο� ��Ʈ");
	TextOut(getMemDC(), 100, 300, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);*/
}

void secondScene::showItem(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_showItem = false;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_buccanary->getRect(), _ptMouse))
		{
			_showItem = true;
		}
		shopWindow();
	}
	
}
