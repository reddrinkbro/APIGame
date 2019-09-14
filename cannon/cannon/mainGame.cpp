#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//�̰����� �ʱ�ȭ

	_cannon.angle = PI / 2;				 //90���� ������ �����
	_cannon.length = 80;				 //���ű��� 80
	_cannon.radius = 50;				 //ĳ�� ���� ������
	_cannon.center.x = WINSIZEX / 2;	 //ĳ�� x��ǥ
	_cannon.center.y = WINSIZEY;		 //ĳ�� y��ǥ
	_bullet.bulletAngle = 0;
	isShoot = false;
	deltaX = 0;
	deltaY = 0;
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

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_cannon.angle > PI / 6 && _cannon.angle < PI / 6 * 5)
		{
			_cannon.angle -= 0.04f;
		}
		else if (_cannon.angle <= PI / 6)
		{
			_cannon.angle = PI / 6 + 0.01;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_cannon.angle > PI / 6 && _cannon.angle < PI / 6 * 5)
		{
			_cannon.angle += 0.04f;
		}
		else if (_cannon.angle >  PI / 6 * 5)
		{
			_cannon.angle = PI / 6 * 5 - 0.01;
		}
	}
	//���� ������ x, y��ǥ�� ������ ���� ��� ������Ʈ
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.length + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.length + _cannon.center.y;
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_bullet.rc = RectMake(_cannon.cannonEnd.x, _cannon.cannonEnd.y,30, 30);
		if (bulletVec.size() < 5)
		{
			bulletVec.push_back(_bullet);
		}
		isShoot = true;
	}
	
	for (int i = 0; i < bulletVec.size(); i++)
	{
		if (isShoot)
		{
			if (bulletVec[i].bulletAngle != 0)continue;
			bulletVec[i].bulletAngle = _cannon.angle;
		}
	}
	fire();
	intersect();
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	//���� �׸���
	
	sprintf(str, "%f", cosf(_cannon.angle));
	TextOut(hdc, 0, 0, str, strlen(str));

	LineMake(hdc, _cannon.center.x, _cannon.center.y,
		_cannon.cannonEnd.x, _cannon.cannonEnd.y);

	//ĳ�� �׸���
	EllipseMakeCenter(hdc, _cannon.center.x, _cannon.center.y,
		_cannon.radius * 2, _cannon.radius * 2);
	
	for (int i = 0; i < bulletVec.size();i++)
	{
		if (isShoot)
		{
			EllipseMakeCenter(hdc, bulletVec[i].rc.left, bulletVec[i].rc.top, 30, 30);
		}
	}
}

void mainGame::fire(void)
{
	for (int i = 0; i < bulletVec.size();i++)
	{
		
		bulletVec[i].rc.left += cosf(bulletVec[i].bulletAngle) * 10;
		bulletVec[i].rc.right += cosf(bulletVec[i].bulletAngle) * 10;
		bulletVec[i].rc.bottom += -sinf(bulletVec[i].bulletAngle) * 10;
		bulletVec[i].rc.top += -sinf(bulletVec[i].bulletAngle) * 10;
		if (bulletVec[i].rc.left < 0 || bulletVec[i].rc.right > WINSIZEX)
		{
			bulletVec[i].bulletAngle = PI- bulletVec[i].bulletAngle ;
		}
		if (bulletVec[i].rc.top < 0 || bulletVec[i].rc.bottom >WINSIZEY)
		{
			bulletVec[i].bulletAngle = 2 * PI -bulletVec[i].bulletAngle;
		}
	}
}

void mainGame::intersect(void)
{
	RECT rcTemp;
	float temp;
	
	for (int i = 0; i < bulletVec.size();i++)
	{
		for (int j = 0; j < bulletVec.size(); j++)
		{
			deltaX = bulletVec[i].rc.left + (bulletVec[i].rc.right - bulletVec[i].rc.left) / 2 - bulletVec[j].rc.left + (bulletVec[j].rc.right - bulletVec[j].rc.left) / 2;
			deltaY = bulletVec[i].rc.top + (bulletVec[i].rc.bottom - bulletVec[i].rc.top) / 2 - bulletVec[j].rc.top + (bulletVec[j].rc.bottom - bulletVec[j].rc.top) / 2;
			if (i == j)continue;
			if (sqrt(deltaX*deltaX + deltaY*deltaY) <30)
			{
				temp = bulletVec[i].bulletAngle;
				bulletVec[i].bulletAngle = bulletVec[j].bulletAngle;
				bulletVec[j].bulletAngle = temp;
			}
		}
	}
}