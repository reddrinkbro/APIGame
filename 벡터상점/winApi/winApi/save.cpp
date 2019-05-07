#include "stdafx.h"
#include "mainGame.h"

void mainGame::save()
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_save = true;
	}
	if (_save)
	{
		char str[128];
		if (_gameNode == _startScene)
		{
			sprintf(str, "%d", 1);
		}
		else if (_gameNode == _secondScene)
		{
			sprintf(str, "%d", 2);
		}
		_mLoad.clear();
		_mLoad.push_back(str);
		TXTMANAGER->save("map.txt", _mLoad);
		_player->save(_save);
		_save = false;
	}
}