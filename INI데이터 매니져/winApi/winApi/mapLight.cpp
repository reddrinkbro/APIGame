#include "stdafx.h"
#include "mainGame.h"

void mainGame::mapLight()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		char str[128];
		if (PtInRect(&_option->getLeft(), _ptMouse))
		{
			_startScene->setRenderValue(_startScene->getRenderValue() - 10);
			_secondScene->setRenderValue(_secondScene->getRenderValue() - 10);
			if (_startScene->getRenderValue() <= 100) _startScene->setRenderValue(100);
			if (_secondScene->getRenderValue() <= 100) _secondScene->setRenderValue(100);
		}
		else if (PtInRect(&_option->getRight(), _ptMouse))
		{
			_startScene->setRenderValue(_startScene->getRenderValue() + 10);
			_secondScene->setRenderValue(_secondScene->getRenderValue() + 10);
			if (_startScene->getRenderValue() > 255) _startScene->setRenderValue(255);
			if (_secondScene->getRenderValue() > 255) _secondScene->setRenderValue(255);
		}
		sprintf(str, "%d", _startScene->getRenderValue());
		INIDATA->addData("mapLight", "key", str);
		INIDATA->iniSave("option");
	}
}