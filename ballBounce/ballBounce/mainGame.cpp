#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//�̰����� �ʱ�ȭ
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
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	
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
	//������ ���� ������ 25���� �۾����� ����
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
	//���� �Ʒ��� ������ 25���� �۾����� ����
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && moveRect.bottom > moveRect.top + 25)
	{
		moveRect.top += 3;
		moveRect.bottom -= 3;
	}
	//���������� ���� �����϶�
	if (isRight)
	{
		circleRect.left += getBallSpeed();
		circleRect.right += getBallSpeed();
	}
	//�������� ���� �����ϋ�
	else if (!isRight)
	{
		circleRect.left-= getBallSpeed();
		circleRect.right-= getBallSpeed();
	}
	//���� ���� �����ϋ�
	if (isUp)
	{
		circleRect.top-= getBallSpeed();
		circleRect.bottom-= getBallSpeed();
	}
	//�Ʒ��� ���� �����϶�
	else if (!isUp)
	{
		circleRect.top+= getBallSpeed();
		circleRect.bottom+= getBallSpeed();
	}
	//�����ʺ��� �ε�����
	if (moveRect.right < circleRect.right )
	{
		isRight = false;
		circleRect.left-=3;
		circleRect.right-=3;
	}
	//���ʺ��� �ε�����
	else if (moveRect.left > circleRect.left)
	{
		isRight = true;
		circleRect.left += 3;
		circleRect.right += 3;
	}
	//���ʺ��� �ε�����
	else if (moveRect.top > circleRect.top)
	{
		isUp = false;
		circleRect.top += 3;
		circleRect.bottom += 3;
	}
	//�Ʒ��ʺ��� �ε�����
	else if (moveRect.bottom < circleRect.bottom)
	{
		isUp = true;
		circleRect.top -= 3;
		circleRect.bottom -= 3;
	}
	
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	//�̰����� WM_PAINT���� �ߴ����� ó��
	
	Rectangle(hdc, moveRect.left, moveRect.top, moveRect.right, moveRect.bottom);
	EllipseMake(hdc, circleRect.left, circleRect.top, 25, 25);
}
