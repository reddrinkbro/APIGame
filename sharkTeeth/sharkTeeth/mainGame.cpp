#include "stdafx.h"
#include "mainGame.h"
//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//이곳에서 초기화
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
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
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
//	## render(HDC hdc) ## 렌더
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
				TextOut(hdc, WINSIZEY / 2, 100, "패배하였습니다", 14);
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
	//이곳에서 WM_PAINT에서 했던것을 처리

	/*if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}*/
}
