#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init();
	//이곳에서 초기화
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
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	
}

//============================
//	## render(HDC hdc) ## 렌더
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
