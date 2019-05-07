#include "stdafx.h"
#include "mainGame.h"

void mainGame::selectMap()
{
	_mLoad = TXTMANAGER->load("map.txt");
	if (atof(_mLoad[0].c_str()) == 1)
	{
		_gameNode = _startScene;
	}
	else if (atof(_mLoad[0].c_str()) == 2)
	{
		_gameNode = _secondScene;
	}
}