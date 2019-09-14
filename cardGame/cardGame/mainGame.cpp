#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//�̰����� �ʱ�ȭ
	for (int i = 0; i < 16; i++)
	{
		cardMix[i] = i + 1;
	}
	for (int i = 0; i < RND->getFromIntTo(300,1000); i++)
	{
		int index1 = rand() % 16;
		int index2 = rand() % 16; 
		temp = cardMix[index1]; 
		cardMix[index1] = cardMix[index2];
		cardMix[index2] = temp;
	}
	for (int i = 0; i < 16; i++)
	{
		if (cardMix[i] > 8)
		{
			cardMix[i] -= 8;
		}
		_card[i].num = cardMix[i];
	}
	
	for (int i = 0; i < 16; i++)
	{
		_card[i].isCorrect = false;
		_card[i].isClick = false;
		_card[i].isLook = false;
		
	}
	for (int i = 0; i < 16; i++)
	{
		if (i < 4)
		{
			_card[i].rc = RectMake(200 + i * 100,  50, 50, 75);
		}
		else if (i < 8 && i >= 4)
		{
			_card[i].rc = RectMake(200 + (i - 4) * 100, 150, 50, 75);
		}
		else if (i < 12 && i >= 8)
		{
			_card[i].rc = RectMake(200 + (i - 8) * 100, 250, 50, 75);
		}
		else
		{
			_card[i].rc = RectMake(200 + (i - 12) * 100, 350, 50, 75);
		}
	}
	isCheck = false;
	
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
	
}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	for (int i = 0; i < 16;i++)
	{
		Rectangle(hdc, _card[i].rc.left, _card[i].rc.top, _card[i].rc.right, _card[i].rc.bottom);
	}
	
	if (GetKeyState(0x01) & 0x8000)
	{
		for (int i = 0; i < 16;i++)
		{
			if (PtInRect(&_card[i].rc, _ptMouse))
			{
				_card[i].isClick = true;
				_card[i].isLook = true;
			}
		}
	}
	for (int i = 0; i < 16;i++)
	{
		if ((_card[i].isClick &&_card[i].isLook) || _card[i].isCorrect)
		{
			wsprintf(str, "%d", _card[i].num);
			TextOut(hdc, (_card[i].rc.right - _card[i].rc.left) / 2 + _card[i].rc.left, (_card[i].rc.bottom - _card[i].rc.top) / 2 + _card[i].rc.top, str, strlen(str));
		}
	}
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (i == j)
			{
				continue;
			}
			if (_card[i].isLook && _card[j].isLook && _card[i].num == _card[j].num)
			{
				_card[i].isCorrect = true;
				_card[j].isCorrect = true;
			}
			else if(_card[i].isLook && _card[j].isLook && _card[i].num != _card[j].num)
			{
				_card[i].isLook = false;
				_card[j].isLook = false;
			}
		}
	}
}
