#include "stdafx.h"
#include "mainGame.h"

void mainGame::enemyMissileDirection()
{
	float angle = 0;
	for (int i = 0; i < _em->getMinions().size(); i++)
	{
		angle = getAngle(_em->getMinions()[i]->getRect().left, _em->getMinions()[i]->getRect().top,
			_rocket->getRect().left, _rocket->getRect().top);
		_em->getMinions()[i]->getMissile()->fire(_em->getMinions()[i]->getRect().left, _em->getMinions()[i]->getRect().top, angle);
	}
	if (_em->getBoss()->getIsAppear())
	{
		angle = getAngle(_em->getBoss()->getRect().left, _em->getBoss()->getRect().top,
			_rocket->getRect().left, _rocket->getRect().top);
		_em->getBoss()->getMissile()->fire(_em->getBoss()->getRect().left + (_em->getBoss()->getRect().right- _em->getBoss()->getRect().left)/2
			, _em->getBoss()->getRect().bottom);
	}
}