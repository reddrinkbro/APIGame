#include "stdafx.h"
#include "mainGame.h"
//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//�̰����� �ʱ�ȭ
	fail = RND->getInt(8);
	for (int i = 0; i < 8; i++)
	{
		if (i > 3)
		{
			rc[i] = RectMakeCenter((i - 2) * 100 + 50,100 +WINSIZEY / 2, 100, 100);
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

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		rc.left += 3;
		rc.right += 3;
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
	for (int i = 0; i < 8; i++)
	{
		Rectangle(hdc, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
	}
	for (int i = 0; i < 8; i++)
	{
		if (fail == i)
		{
			if (rc[i].left < _ptMouse.x && rc[i].right >_ptMouse.x && rc[i].bottom > _ptMouse.y && rc[i].top < _ptMouse.y)
			{
				TextOut(hdc, WINSIZEY / 2, 100, "�й��Ͽ����ϴ�", 14);
				HBRUSH failRect = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
				HBRUSH failBrush = (HBRUSH)SelectObject(hdc,failRect);
				Rectangle(hdc, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
				SelectObject(hdc, failBrush);
				DeleteObject(failRect);
				Sleep(1000);
				exit(0);
			}
		}
		else
		{
			if (rc[i].left < _ptMouse.x && rc[i].right >_ptMouse.x && rc[i].bottom > _ptMouse.y && rc[i].top < _ptMouse.y)
			{
				HBRUSH sucessRect = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
				HBRUSH sucessBrush = (HBRUSH)SelectObject(hdc, sucessRect);
				Rectangle(hdc, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
				SelectObject(hdc, sucessBrush);
				DeleteObject(sucessRect);
			}
		}
	}
	//�̰����� WM_PAINT���� �ߴ����� ó��

	/*if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}*/
}
