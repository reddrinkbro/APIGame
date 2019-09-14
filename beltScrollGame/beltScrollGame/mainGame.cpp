#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//이곳에서 초기화
	player = RectMake(WINSIZEX / 2, 750 , 30, 30);
	bullet = RectMake(WINSIZEX /2 , 750, 30, 30);
	playerHp = RectMake(player.left, player.top - 10, 30, 5);
	object = RectMake(RND->getInt(WINSIZEX), -RND->getInt(WINSIZEY * 2), 30, 30);
	isBulletActive = false;
	isBulletMove = false;
	time = RND->getFromIntTo(2,4);
	score = 0;
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
	object = RectMake(RND->getInt(WINSIZEX), -RND->getInt(WINSIZEY * 2), 30, 30); // 장애물 랜덤소환
	if (objectVec.size() < 50) //장애물 수
	{
		objectVec.push_back(object);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && player.left >0) //플레이어 이동
	{
		player.left -= 3;
		player.right -= 3;
		bullet.left = player.left;
		bullet.right = player.right;
		playerHp.left -= 3;
		playerHp.right -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && player.right < WINSIZEX)
	{
		player.left += 3;
		player.right += 3;
		bullet.left = player.left;
		bullet.right = player.right;
		playerHp.left += 3;
		playerHp.right += 3;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) //총알발사버튼
	{
		if (bulletVec.size() < 5)
		{
			bulletVec.push_back(bullet);
		}
		isBulletMove = true;
	}
	
	if (isBulletMove) //총알발사시 총알이동
	{
		for (int i = 0; i < bulletVec.size(); i++)
		{
			bulletVec[i].top -= 20;
			bulletVec[i].bottom -= 20;
			isBulletActive = true;
			if (bulletVec[i].top < 0)
			{
				InvalidateRect(_hWnd, &bulletVec[i], true);
				isBulletActive = false;
				bulletVec.erase(bulletVec.begin());
			}
		}
	}
	
	for (int i = 0; i < objectVec.size(); i++) // 장애물이 바닥에 닿았을때
	{
			
		objectVec[i].top += 5;
		objectVec[i].bottom += 5;
				
		if (objectVec[i].bottom > WINSIZEY)
		{
			objectVec.erase(objectVec.begin()+i);
		}
	}
	for (int i = 0; i < objectVec.size(); i++)
	{
		for (int j = 0; j < bulletVec.size(); j++)
		{
			if (IntersectRect(&rcTemp, &bulletVec[j], &objectVec[i])) //총알에 부딪쳤을때
			{
				InvalidateRect(_hWnd, &bulletVec[j], true);
				InvalidateRect(_hWnd, &objectVec[i], true);
				bulletVec.erase(bulletVec.begin());
				objectVec.erase(objectVec.begin() + i);
			}
		}
	}
	for (int i = 0; i < objectVec.size(); i++) 
	{
		if (objectVec[i].bottom > player.top && objectVec[i].left < player.right && objectVec[i].right > player.left && objectVec[i].top < player.bottom) //오브젝트와 충돌
		{
			playerHp.left++;
			InvalidateRect(_hWnd, &objectVec[i], true);
			objectVec.erase(objectVec.begin() + i);
		}
	}
	score++;
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(HDC hdc)
{
	//이곳에서 WM_PAINT에서 했던것을 처리
	char str[128];
	
	Rectangle(hdc, player.left, player.top, player.right, player.bottom);
	if (playerHp.right - playerHp.left <= 12) //체력바설정
	{
		HBRUSH rectColor = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldColor = (HBRUSH)SelectObject(hdc, rectColor);
		Rectangle(hdc, playerHp.left, playerHp.top, playerHp.right, playerHp.bottom);
		SelectObject(hdc, oldColor);
		DeleteObject(rectColor);
	}
	else if (playerHp.right - playerHp.left > 12 &&  playerHp.right - playerHp.left < 24)
	{
		HBRUSH rectColor = (HBRUSH)CreateSolidBrush(RGB(255,102,0));
		HBRUSH oldColor = (HBRUSH)SelectObject(hdc, rectColor);
		Rectangle(hdc, playerHp.left, playerHp.top, playerHp.right, playerHp.bottom);
		SelectObject(hdc, oldColor);
		DeleteObject(rectColor);
	}
	else
	{
		HBRUSH rectColor = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH oldColor = (HBRUSH)SelectObject(hdc, rectColor);
		Rectangle(hdc, playerHp.left, playerHp.top, playerHp.right, playerHp.bottom);
		SelectObject(hdc, oldColor);
		DeleteObject(rectColor);
	}
	
	wsprintf(str, "현재 점수 : %d", score /65);
	TextOut(hdc, 0, 0, str, strlen(str));

	for (int i = 0; i < bulletVec.size(); i++)
	{
		if (isBulletActive)
		{
			EllipseMake(hdc, bulletVec[i].left, bulletVec[i].top, 30, 30);
		}
	}
	for (int i= 0; i < objectVec.size(); i++)
	{
		if (objectVec[i].top > 50)
		{
			Rectangle(hdc, objectVec[i].left, objectVec[i].top, objectVec[i].right, objectVec[i].bottom);
		}
		if (playerHp.right - playerHp.left == 0)
		{

			wsprintf(str, "점수 : %d", score / 65);
			TextOut(hdc, WINSIZEX / 2 - 50, WINSIZEY / 2 - 100, str, strlen(str));
			TextOut(hdc, WINSIZEX / 2 - 50, WINSIZEY / 2 - 50, "게임 끝", strlen("게임 끝"));
			Sleep(1000);
			exit(0);
		}
	}
}
