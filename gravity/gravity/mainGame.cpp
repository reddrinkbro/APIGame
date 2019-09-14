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
	isShoot = true;
	_bullet.time = 0;
	time2 = 1;
	_bullet.gravity = 9.8f;
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
	for (int i = 0; i < bulletVec.size(); i++)
	{
		if (isShoot)
		{
			if (bulletVec[i].bulletAngle != 0)continue;
			bulletVec[i].bulletAngle = _cannon.angle;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_bullet.rc = RectMake(_cannon.cannonEnd.x, _cannon.cannonEnd.y, 30, 30);
		if (bulletVec.size() < 100)
		{
			bulletVec.push_back(_bullet);
		}
	}
	for (int i = 0; i < bulletVec.size(); i++)
	{
		if (bulletVec[i].time <= time2)
		{
			bulletVec[i].time += 0.01;
		}
	}
	fire();
	
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	//���� �׸���
	
	LineMake(hdc, _cannon.center.x, _cannon.center.y,
		_cannon.cannonEnd.x, _cannon.cannonEnd.y);

	//ĳ�� �׸���
	EllipseMakeCenter(hdc, _cannon.center.x, _cannon.center.y,
		_cannon.radius * 2, _cannon.radius * 2);
	
	for (int i = 0; i < bulletVec.size();i++)
	{
		if (isShoot)
		{
			EllipseMakeCenter(hdc, bulletVec[i].rc.left, bulletVec[i].rc.top, 20, 20);
		}
	}
	
}

void mainGame::fire(void)
{
	for (int i = 0; i < bulletVec.size();i++)
	{
		if (bulletVec[i].time > time2)
		{
			bulletVec[i].rc.left += cosf(bulletVec[i].bulletAngle) * 10;
			bulletVec[i].rc.right += cosf(bulletVec[i].bulletAngle) * 10;
			bulletVec[i].rc.bottom += (sinf(bulletVec[i].bulletAngle) * 10 - (bulletVec[i].gravity*bulletVec[i].time));
			bulletVec[i].rc.top += (sinf(bulletVec[i].bulletAngle) * 10 - (bulletVec[i].gravity*bulletVec[i].time));
			bulletVec[i].gravity -= 9.8f/100;
		}
		else
		{
			bulletVec[i].rc.left += cosf(bulletVec[i].bulletAngle) * 10;
			bulletVec[i].rc.right += cosf(bulletVec[i].bulletAngle) * 10;
			bulletVec[i].rc.bottom += -(sinf(bulletVec[i].bulletAngle) * 10 - (bulletVec[i].gravity*bulletVec[i].time));
			bulletVec[i].rc.top += -(sinf(bulletVec[i].bulletAngle) * 10 - (bulletVec[i].gravity*bulletVec[i].time));
		}

	}
}
