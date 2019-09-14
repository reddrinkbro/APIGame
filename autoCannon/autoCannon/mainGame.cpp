#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//이곳에서 초기화

	_cannon.angle = PI / 2;				 //90도로 포신을 세운다
	_cannon.length = 80;				 //포신길이 80
	_cannon.radius = 50;				 //캐논 몸통 반지름
	_cannon.center.x = WINSIZEX / 2;	 //캐논 x좌표
	_cannon.center.y = WINSIZEY;		 //캐논 y좌표
	_bullet.bulletAngle = 0;
	isShoot = true;
	_bullet.time = 0;
	time2 = 1;
	_bullet.gravity = 9.8f;
	_bullet.height = 0; //최고 높이
	isRight = true;
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
	
	if (isRight) { _cannon.angle -= 0.01f; }
	else { _cannon.angle += 0.01f; }
	if (_cannon.angle <= PI / 6)
	{
		isRight = false;
	}
	else if (_cannon.angle > PI / 6 * 5)
	{
		isRight = true;
	}
	//포신 끝점의 x, y좌표를 각도에 따라 계속 업데이트
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.length + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.length + _cannon.center.y;
	for (int i = 0; i < bulletVec.size(); i++)
	{
		if (isShoot)
		{
			if (bulletVec[i].bulletAngle != 0)continue;
			bulletVec[i].bulletAngle = _cannon.angle;
			bulletVec[i].height = 5 * 5 * -sinf(bulletVec[i].bulletAngle)*-sinf(bulletVec[i].bulletAngle) / (2 * 9.8);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_bullet.rc = RectMake(_cannon.cannonEnd.x, _cannon.cannonEnd.y, 30, 30);
		if (bulletVec.size() < 5)
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
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	//포신 그리기
	
	LineMake(hdc, _cannon.center.x, _cannon.center.y,
		_cannon.cannonEnd.x, _cannon.cannonEnd.y);

	//캐논 그리기
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
