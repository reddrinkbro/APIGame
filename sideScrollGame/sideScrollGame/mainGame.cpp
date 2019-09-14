#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//�̰����� �ʱ�ȭ

	_player[0] = RectMake(100, WINSIZEY / 2, 50, 50);
	_playerHealth[0] = RectMake(0, 0, WINSIZEX/2 -50, 50);
	_player[1] = RectMake(WINSIZEX - 100, WINSIZEY / 2, 50, 50);
	_playerHealth[1] = RectMake(WINSIZEX / 2 +50, 0,350, 50);
	int width = 0;
	for (int i = 0; i < 6; i++)
	{
		if (i < 3)
		{
			width++;
		}
		else
		{
			width--;
		}
		skill1._skillRect[i] = RectMake(i * 100 - 600, 50, WINSIZEX / 2 - 300, WINSIZEY / 2 - width * 50);
	}
	width = 0;
	for (int i = 0; i < 6;i++)
	{
		if (i < 3)
		{
			width++;
		}
		else
		{
			width--;
		}
		skill1._skillRect[i + 6] = RectMake(i * 100 - 600, WINSIZEY / 2 + 150 - width * 30, 100, WINSIZEY);
	}
	_skill[2] = 30;
	skill1.isUsing = true;
	for (int i = 0; i < 2; i++)
	{
		_bullet[i] = RectMake(_player[i].left, _player[i].top, 30, 30);
		isBulletActive[i] = false;
		isBulletMove[i] = false;
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
	player2_skill();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//1p
	if (GetKeyState(0x57) & 0x8000 && _player[0].top > 50) //��������
	{
		_player[0].top -= 3;
		_player[0].bottom -= 3;
		_bullet[0].top = _player[0].top;
		_bullet[0].bottom = _player[0].bottom;
	}

	if (GetKeyState(0x53) & 0x8000 && _player[0].bottom < WINSIZEY) // �Ʒ�������
	{
		_player[0].top += 3;
		_player[0].bottom += 3;
		_bullet[0].top = _player[0].top;
		_bullet[0].bottom = _player[0].bottom;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) //�Ѿ� ������
	{
		if (_playerBullet1.size() < 5)
		{
			_playerBullet1.push_back(_bullet[0]);
		}
		isBulletMove[0] = true;

	}
	//�÷��̾� 1 ù��° ��ų
	if (GetKeyState(0x31) & 0x0001 && skill1.isUsing)
	{
		if (skill1._skillRect[0].left > WINSIZEX)
		{
			skill1.isUsing = false; //��ų �ѹ��� ���
			for (int i = 0; i < 12; i++)
			{
				skill1._skillRect[i].left -= (WINSIZEX + 620);
				skill1._skillRect[i].right -= (WINSIZEX + 620);
			}
		}
		for (int i = 0; i < 12; i++)
		{
			skill1._skillRect[i].left += 10;
			skill1._skillRect[i].right += 10;
		}
		for (int i = 0; i < 12; i++)
		{
			if (IntersectRect(&rcTemp, &_player[1], &skill1._skillRect[i]))
			{
				_playerHealth[1].right -= 10 ;
				InvalidateRect(_hWnd, &skill1._skillRect[i], true);
			}
		}
		
	}
	if (isBulletMove[0])
	{
		for (int i = 0; i < _playerBullet1.size(); i++) //�Ѿ� �߻�
		{
			_playerBullet1[i].left += 20;
			_playerBullet1[i].right += 20;
			isBulletActive[0] = true;
			if (_playerBullet1[i].right > WINSIZEX)
			{
				InvalidateRect(_hWnd, &_playerBullet1[i], true);
				isBulletActive[0] = false;
				_playerBullet1.erase(_playerBullet1.begin());
			}
		}
	}

	//�Ѿ� ����
	for (int i = 0; i < _playerBullet1.size(); i++)
	{
		if (IntersectRect(&rcTemp, &_player[1], &_playerBullet1[i]))
		{
			_playerHealth[1].right -= 10;
			InvalidateRect(_hWnd, &_playerBullet1[i], true);
			_playerBullet1.erase(_playerBullet1.begin());
		}
	}
	//2p
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player[1].top > 50) //����
	{
		_player[1].top -= 3;
		_player[1].bottom -= 3;
		_bullet[1].top = _player[1].top;
		_bullet[1].bottom = _player[1].bottom;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player[1].bottom < WINSIZEY) //�Ʒ�
	{
		_player[1].top += 3;
		_player[1].bottom += 3;
		_bullet[1].top = _player[1].top;
		_bullet[1].bottom = _player[1].bottom;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0)) // �е� 0Ű ������ �߻�
	{
		if (_playerBullet2.size() < 5)
		{
			_playerBullet2.push_back(_bullet[1]);
		}
		isBulletMove[1] = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD1) && _skill[2] >0) //�÷��̾� 2 ��ų
	{
		if (_playerBullet2.size() < 40)
		{
			_playerBullet2.push_back(_bullet[1]);
		}
		isBulletMove[1] = true;
		_skill[2] -= 1;
	}

	if (isBulletMove[1])
	{
		for (int i = 0; i < _playerBullet2.size(); i++)
		{
			if (direct == UP)//������ ���ʿ� ������
			{
				_playerBullet2[i].top -= 3;
				_playerBullet2[i].bottom -= 3;
				_playerBullet2[i].left -= 20;
				_playerBullet2[i].right -= 20;
			}
			else if (direct == DOWN)//������ �Ʒ��ʿ� ������
			{
				_playerBullet2[i].top += 3;
				_playerBullet2[i].bottom += 3;
				_playerBullet2[i].left -= 20;
				_playerBullet2[i].right -= 20;
			}
			else if (direct == CENTER)//������ ����� ������
			{
				_playerBullet2[i].left -= 20;
				_playerBullet2[i].right -= 20;
			}
			isBulletActive[1] = true;
			if (_playerBullet2[i].left < 0)
			{
				InvalidateRect(_hWnd, &_playerBullet2[i], true);
				isBulletActive[1] = false;
				_playerBullet2.erase(_playerBullet2.begin());
			}
		}
	}
	for (int i = 0; i < _playerBullet2.size(); i++)
	{
		if (IntersectRect(&rcTemp, &_player[0], &_playerBullet2[i]))
		{
			_playerHealth[0].left += 10;
			InvalidateRect(_hWnd, &_playerBullet2[i], true);
			_playerBullet2.erase(_playerBullet2.begin());
		}
	}
	for (int i = 0; i < _playerBullet2.size(); i++)
	{
		//for (int j = 0; j < 12; j++)
		//{
			if (IntersectRect(&rcTemp, &_playerBullet2[i], &skill1._skillRect[11]))
			{
				InvalidateRect(_hWnd, &_playerBullet2[i], true);
				_playerBullet2.erase(_playerBullet2.begin());
			}
			else if (IntersectRect(&rcTemp, &_playerBullet2[i], &skill1._skillRect[5]))
			{
				InvalidateRect(_hWnd, &_playerBullet2[i], true);
				_playerBullet2.erase(_playerBullet2.begin());
			}
			else if (IntersectRect(&rcTemp, &_playerBullet2[i], &skill1._skillRect[0]))
			{
				InvalidateRect(_hWnd, &_playerBullet2[i], true);
				_playerBullet2.erase(_playerBullet2.begin());
			}
			else if (IntersectRect(&rcTemp, &_playerBullet2[i], &skill1._skillRect[6]))
			{
				InvalidateRect(_hWnd, &_playerBullet2[i], true);
				_playerBullet2.erase(_playerBullet2.begin());
			}
		//}
	}
	
	
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	//�̰����� WM_PAINT���� �ߴ����� ó��
	char str[128];
	
	for (int i = 0; i < 2; i++) //�÷��̾�� ü�¹�
	{
		Rectangle(hdc, _player[i].left, _player[i].top, _player[i].right, _player[i].bottom);
		Rectangle(hdc, _playerHealth[i].left, _playerHealth[i].top, _playerHealth[i].right, _playerHealth[i].bottom);
	}
	for (int i = 0; i < 12; i++) //1����ų �簢��
	{
		Rectangle(hdc, skill1._skillRect[i].left, skill1._skillRect[i].top, skill1._skillRect[i].right, skill1._skillRect[i].bottom);
	}
	for (int i = 0; i < _playerBullet1.size(); i++) // �Ѿ�
	{
		if (isBulletActive[0])
		{
			EllipseMake(hdc, _playerBullet1[i].left, _playerBullet1[i].top, 30, 30);
		}
	}
	for (int i = 0; i < _playerBullet2.size(); i++)
	{
		if (isBulletActive[1])
		{
			EllipseMake(hdc, _playerBullet2[i].left, _playerBullet2[i].top, 30, 30);
		}
	}
	if (_playerHealth[0].right - _playerHealth[0].left == 0)
	{

		TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, "2p WIN", strlen("2p WIN"));
		Sleep(1000);
		exit(0);

	}
	else if (_playerHealth[1].right - _playerHealth[1].left == 0)
	{
		TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, "1p WIN", strlen("1p WIN"));
		Sleep(1000);
		exit(0);
	}
	
}

void mainGame::player2_skill(void)
{
	if (_player[0].bottom < _player[1].top)
	{
		direct = UP;
	}
	else if (_player[0].top > _player[1].bottom)
	{
		direct = DOWN;
	}
	else
	{
		direct = CENTER;
	}
}
