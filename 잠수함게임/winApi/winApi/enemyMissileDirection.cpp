#include "stdafx.h"
#include "mainGame.h"

void mainGame::enemyMissileDirection()
{
	float angle = 0;
	for (int i = 0; i < _em->getMinions().size(); i++)
	{
		angle = getAngle(_em->getMinions()[i]->getRect().left, _em->getMinions()[i]->getRect().top,
			_rocket->getRect().left, _rocket->getRect().top);
		if (_rocket->getRect().left > _em->getMinions()[i]->getRect().left &&_rocket->getRect().right < _em->getMinions()[i]->getRect().right)
		{
			_em->getMinions()[i]->getMissile()->fire(_em->getMinions()[i]->getRect().left + (_em->getMinions()[i]->getRect().right - _em->getMinions()[i]->getRect().left) / 2
				, _em->getMinions()[i]->getRect().top, angle);
		}
	}
	for (int i = 0; i < _em->getBoat().size(); i++)
	{
		if (_rocket->getRect().left > _em->getBoat()[i]->getRect().left &&_rocket->getRect().right < _em->getBoat()[i]->getRect().right)
		{
			angle = getAngle(_em->getBoat()[i]->getRect().left, _em->getBoat()[i]->getRect().top,
				_rocket->getRect().left, _rocket->getRect().top);
			_em->getBoat()[i]->getMissile()->fire(_em->getBoat()[i]->getRect().left + (_em->getBoat()[i]->getRect().right - _em->getBoat()[i]->getRect().left) / 2
				, _em->getBoat()[i]->getRect().bottom);
		}
	}
	for (int i = 0; i < _em->getHeli().size(); i++)
	{
		if (_rocket->getRect().left > _em->getHeli()[i]->getRect().left &&_rocket->getRect().right < _em->getHeli()[i]->getRect().right)
		{
			angle = getAngle(_em->getHeli()[i]->getRect().left, _em->getHeli()[i]->getRect().top,
				_rocket->getRect().left, _rocket->getRect().top);
			_em->getHeli()[i]->getMissile()->fire(_em->getHeli()[i]->getRect().left + (_em->getHeli()[i]->getRect().right - _em->getHeli()[i]->getRect().left) / 2
				, _em->getHeli()[i]->getRect().bottom);
		}
	}
}