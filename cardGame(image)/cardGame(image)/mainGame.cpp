#include "stdafx.h"
#include "mainGame.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화
	IMAGEMANAGER->addImage("1", "1.bmp", 56, 87,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("3", "3.bmp", 56, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("8", "8.bmp", 56, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("11", "11.bmp", 56, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("12", "12.bmp", 56, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("홍", "홍.bmp", 56, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("청", "청.bmp", 56, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("단", "단.bmp", 56, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒷면", "뒷면.bmp", 56, 87, true, RGB(255, 0, 255));
	for (int i = 0; i < 16; i++)
	{
		cardMix[i] = i + 1;
	}
	for (int i = 0; i < RND->getFromIntTo(300, 1000); i++)
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
			_card[i].rc = RectMake(200 + i * 100, 50, 56, 87);
		}
		else if (i < 8 && i >= 4)
		{
			_card[i].rc = RectMake(200 + (i - 4) * 100, 150, 56, 87);
		}
		else if (i < 12 && i >= 8)
		{
			_card[i].rc = RectMake(200 + (i - 8) * 100, 250, 56, 87);
		}
		else
		{
			_card[i].rc = RectMake(200 + (i - 12) * 100, 350, 56, 87);
		}

	}
	isClick = false;
	_count = 0;
	_time = 0;
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
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 16;i++)
		{
			if (PtInRect(&_card[i].rc, _ptMouse))
			{
				_card[i].isClick = true;
				_card[i].isLook = true;
				isClick = true;
			}
		}
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (isClick)
		{
			_count++;
		}
		isClick = false;
	}
	if (_count > 1)
	{
		_time += 0.04f;
	}
	if (_time >= 1)
	{
		_count = 0;
	}
	
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다		
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(HDC hdc)
{
	char str[128];
	//흰색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	sprintf(str, " %d %f", _count,_time);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
	for (int i = 0; i < 16;i++)
	{
		IMAGEMANAGER->render("뒷면", getMemDC(), _card[i].rc.left, _card[i].rc.top);
		//Rectangle(getMemDC(), _card[i].rc.left, _card[i].rc.top, _card[i].rc.right, _card[i].rc.bottom);
	}
	for (int i = 0; i < 16;i++)
	{
		if ((_card[i].isClick &&_card[i].isLook) || _card[i].isCorrect)
		{
			switch (_card[i].num)
			{
				case 1:
				{
					IMAGEMANAGER->render("1", getMemDC(), _card[i].rc.left, _card[i].rc.top);
				}
				break;
				case 2:
				{
					IMAGEMANAGER->render("3", getMemDC(), _card[i].rc.left, _card[i].rc.top);
				}
				break;
				case 3:
				{
					IMAGEMANAGER->render("8", getMemDC(), _card[i].rc.left, _card[i].rc.top);
				}
				break;
				case 4:
				{
					IMAGEMANAGER->render("11", getMemDC(), _card[i].rc.left, _card[i].rc.top);
				}
				break;
				case 5:
				{
					IMAGEMANAGER->render("12", getMemDC(), _card[i].rc.left, _card[i].rc.top);
				}
				break;
				case 6:
				{
					IMAGEMANAGER->render("홍", getMemDC(), _card[i].rc.left, _card[i].rc.top);
				}
				break;
				case 7:
				{
					IMAGEMANAGER->render("청", getMemDC(), _card[i].rc.left, _card[i].rc.top);
				}
				break;
				case 8:
				{
					IMAGEMANAGER->render("단", getMemDC(), _card[i].rc.left, _card[i].rc.top);
				}
				break;
			}
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
			else if (_card[i].isLook && _card[j].isLook && _card[i].num != _card[j].num)
			{
				if (_time > 1)
				{
					_time = 0;
					_card[i].isLook = false;
					_card[j].isLook = false;
				}
			}
		}
	}
	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(getHDC());
}
