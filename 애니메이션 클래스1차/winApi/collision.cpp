#include "stdafx.h"
#include "mainGame.h"

void mainGame::collision(void)
{
	for (int i = 0; i < _rocket->getMissile()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getMissile()->getBullet()[i].rc,
				//&_em->getMinions()[j]->getRect()))
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(),40, 30)))
			{
				_rocket->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

	for (int i = 0; i < _rocket->getBeam()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getBeam()->getBullet()[i].rc,
				//&_em->getMinions()[j]->getRect()))
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				_em->removeMinion(j);
				break;
			}
		}
	}
}