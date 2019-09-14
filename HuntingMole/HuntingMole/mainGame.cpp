#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//�̰����� �ʱ�ȭ
	score = 0;
	gameSpeed = 1500;
	for (int i = 0; i < 8; i++)
	{
		if (i > 3)
		{
			rc[i] = RectMakeCenter((i - 2) * 100 + 50, 100 + WINSIZEY / 2,100, 100);
		}
		else
		{
			rc[i] = RectMakeCenter((i + 2) * 100 + 50, WINSIZEY / 2, 100, 100);
		}
	}
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
	if (rc[randNum].left < _ptMouse.x && rc[randNum].right >_ptMouse.x && rc[randNum].bottom > _ptMouse.y && rc[randNum].top < _ptMouse.y)
	{
		score++;
		_ptMouse.x = 0;
		_ptMouse.y = 0;
	}
	
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	/*
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		rc.top -= 3;
		rc.bottom -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		rc.left -= 3;
		rc.right -= 3;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		rc.left += 20;
		rc.right += 20;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		rc.top += 3;
		rc.bottom += 3;
	}*/
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	//�̰����� WM_PAINT���� �ߴ����� ó��
	RectangleMake(hdc, 100, 50, 600, 200);
	RectangleMake(hdc, 100, 200, 600, 400);
	TextOut(hdc, 350, 70, "�δ��� ����", strlen("�δ��� ����"));
	TextOut(hdc, WINSIZEX / 3, 100, "������ �ٲ�� ���� ��������", strlen("������ �ٲ�� ���� ��������"));
	wsprintf(str, "���� : %d", score);
	TextOut(hdc, WINSIZEX / 3, 150, str, strlen(str));
	for (int i = 0; i < 8; i++)
	{
		EllipseMake(hdc, rc[i].left, rc[i].top, 100, 100);
		randNum = RND->getInt(8);
	}
	for (int i = 0; i < 8; i++)
	{
		if (i == randNum)
		{
			HBRUSH rect = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
			HBRUSH oldRect = (HBRUSH)SelectObject(hdc, rect);
			EllipseMake(hdc, rc[i].left, rc[i].top, 100, 100);
			SelectObject(hdc, oldRect);
			DeleteObject(rect);
			Sleep(gameSpeed);
			gameSpeed-=2;
		}
	}
}
