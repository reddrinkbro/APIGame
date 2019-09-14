#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//�̰����� �ʱ�ȭ
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
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	object = RectMake(RND->getInt(WINSIZEX), -RND->getInt(WINSIZEY * 2), 30, 30); // ��ֹ� ������ȯ
	if (objectVec.size() < 50) //��ֹ� ��
	{
		objectVec.push_back(object);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && player.left >0) //�÷��̾� �̵�
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
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) //�Ѿ˹߻��ư
	{
		if (bulletVec.size() < 5)
		{
			bulletVec.push_back(bullet);
		}
		isBulletMove = true;
	}
	
	if (isBulletMove) //�Ѿ˹߻�� �Ѿ��̵�
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
	
	for (int i = 0; i < objectVec.size(); i++) // ��ֹ��� �ٴڿ� �������
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
			if (IntersectRect(&rcTemp, &bulletVec[j], &objectVec[i])) //�Ѿ˿� �ε�������
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
		if (objectVec[i].bottom > player.top && objectVec[i].left < player.right && objectVec[i].right > player.left && objectVec[i].top < player.bottom) //������Ʈ�� �浹
		{
			playerHp.left++;
			InvalidateRect(_hWnd, &objectVec[i], true);
			objectVec.erase(objectVec.begin() + i);
		}
	}
	score++;
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	//�̰����� WM_PAINT���� �ߴ����� ó��
	char str[128];
	
	Rectangle(hdc, player.left, player.top, player.right, player.bottom);
	if (playerHp.right - playerHp.left <= 12) //ü�¹ټ���
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
	
	wsprintf(str, "���� ���� : %d", score /65);
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

			wsprintf(str, "���� : %d", score / 65);
			TextOut(hdc, WINSIZEX / 2 - 50, WINSIZEY / 2 - 100, str, strlen(str));
			TextOut(hdc, WINSIZEX / 2 - 50, WINSIZEY / 2 - 50, "���� ��", strlen("���� ��"));
			Sleep(1000);
			exit(0);
		}
	}
}
