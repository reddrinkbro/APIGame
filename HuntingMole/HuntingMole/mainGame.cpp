#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//이곳에서 초기화
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
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용
}

//=============================
//	## update(void) ## 업데이트
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
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	//이곳에서 WM_PAINT에서 했던것을 처리
	RectangleMake(hdc, 100, 50, 600, 200);
	RectangleMake(hdc, 100, 200, 600, 400);
	TextOut(hdc, 350, 70, "두더지 게임", strlen("두더지 게임"));
	TextOut(hdc, WINSIZEX / 3, 100, "색깔이 바뀌는 원을 누르세요", strlen("색깔이 바뀌는 원을 누르세요"));
	wsprintf(str, "점수 : %d", score);
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
