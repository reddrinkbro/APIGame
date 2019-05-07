#include "stdafx.h"
#include "mainGame.h"

void mainGame::showBoss()
{
	if (_rocket->getScore() > 30)
	{
		_em->appearBoss();
	}
}