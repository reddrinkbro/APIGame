#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//이곳에서 초기화
	isRight = true;
	isUp = true;
	moveRect = RectMake(WINSIZEX / 4, WINSIZEY / 4, 400, 400);
	circleRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2+50, 25, 25);
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
	
	if (KEYMANAGER->isStayKeyDown(VK_UP) && moveRect.top >5)
	{
		moveRect.top -= 3;
		moveRect.bottom += 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && moveRect.left >5)
	{
		moveRect.left -= 3;
		moveRect.right += 3;
	}
	//오른쪽 왼쪽 간격이 25보다 작아질수 없다
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && moveRect.right > moveRect.left + 25)
	{
		moveRect.left += 3;
		moveRect.right -= 3;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && moveRect.left <= 5)
	{
		moveRect.left += 3;
		moveRect.right += 3;
	}
	//위쪽 아래쪽 간격이 25보다 작아질수 없다
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && moveRect.bottom > moveRect.top + 25)
	{
		moveRect.top += 3;
		moveRect.bottom -= 3;
	}
	//오른쪽으로 공이 움직일때
	if (isRight)
	{
		circleRect.left += getBallSpeed();
		circleRect.right += getBallSpeed();
	}
	//왼쪽으로 공이 움직일떄
	else if (!isRight)
	{
		circleRect.left-= getBallSpeed();
		circleRect.right-= getBallSpeed();
	}
	//위로 공이 움직일떄
	if (isUp)
	{
		circleRect.top-= getBallSpeed();
		circleRect.bottom-= getBallSpeed();
	}
	//아래로 공이 움직일때
	else if (!isUp)
	{
		circleRect.top+= getBallSpeed();
		circleRect.bottom+= getBallSpeed();
	}
	//오른쪽벽에 부딪힐때
	if (moveRect.right < circleRect.right )
	{
		isRight = false;
		circleRect.left-=3;
		circleRect.right-=3;
	}
	//왼쪽벽에 부딪힐떄
	else if (moveRect.left > circleRect.left)
	{
		isRight = true;
		circleRect.left += 3;
		circleRect.right += 3;
	}
	//위쪽벽에 부딪힐떄
	else if (moveRect.top > circleRect.top)
	{
		isUp = false;
		circleRect.top += 3;
		circleRect.bottom += 3;
	}
	//아래쪽벽에 부딪힐때
	else if (moveRect.bottom < circleRect.bottom)
	{
		isUp = true;
		circleRect.top -= 3;
		circleRect.bottom -= 3;
	}
	
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(HDC hdc)
{
	//이곳에서 WM_PAINT에서 했던것을 처리
	
	Rectangle(hdc, moveRect.left, moveRect.top, moveRect.right, moveRect.bottom);
	EllipseMake(hdc, circleRect.left, circleRect.top, 25, 25);
}
