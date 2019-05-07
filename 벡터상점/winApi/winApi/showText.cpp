#include "stdafx.h"
#include "secondScene.h"

void secondScene::showText()
{
	if (PtInRect(&_rc[0], _ptMouse))
	{
		for (int i = 0; i < _sVec[0].size(); i++)
		{
			SetTextColor(getMemDC(), RGB(0, 0, 0));
			SetBkMode(getMemDC(), TRANSPARENT);
			TextOut(getMemDC(), _rc[0].left, _rc[0].bottom + 10 + i * 20, _sVec[0][i].c_str(), strlen(_sVec[0][i].c_str()));
		}
	}
	if (PtInRect(&_rc[1], _ptMouse))
	{
		for (int i = 0; i <_sVec[1].size(); i++)
		{
			SetTextColor(getMemDC(), RGB(0, 0, 0));
			SetBkMode(getMemDC(), TRANSPARENT);
			TextOut(getMemDC(), _rc[0].left, _rc[0].bottom + 10 + i * 20, _sVec[1][i].c_str(), strlen(_sVec[1][i].c_str()));
		}
	}
}
