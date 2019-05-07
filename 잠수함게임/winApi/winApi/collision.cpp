#include "stdafx.h"
#include "mainGame.h"

void mainGame::collision(void)
{
	//플레이어 공격 , 미사일 일때
	for (int i = 0; i < _rocket->getMissile()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getMissile()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(),0, 30)))
			{
				_rocket->removeMissile(i);
				_missileEffect->show(rc);
				_enemyEffect->show(_em->getMinions()[j]->getRect());
				_em->removeMinion(j);
				_rocket->setScore(_rocket->getScore() + 10);
				break;
			}
		}
	}
	for (int i = 0; i < _rocket->getMissile()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getBoat().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getMissile()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getBoat()[j]->getRect(), 10, 0)))
			{
				_rocket->removeMissile(i);
				_missileEffect->show(rc);
				_rocket->setScore(_rocket->getScore() + 100);
				_em->removeBoat(j);
				break;
			}
		}
	}
	//플레이어 공격,로켓런처일때
	for (int i = 0; i < _rocket->getRocketLauncher()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getRocketLauncher()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 0, 30)))
			{
				_rocket->removeRocketLauncher(i);
				_enemyEffect->show(_em->getMinions()[j]->getRect());
				_rocketLauncherEffect->show(_em->getMinions()[j]->getRect());
				_em->removeMinion(j);
				_rocket->setScore(_rocket->getScore() + 10);
				_rocket->getRocketLauncher()->addBullet();
				break;
			}
		}
	}
	for (int i = 0; i < _rocket->getRocketLauncher()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getBoat().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getRocketLauncher()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getBoat()[j]->getRect(), 10, 40)))
			{
				_rocket->removeRocketLauncher(i);
				_rocketLauncherEffect->show(rc);
				_rocket->setScore(_rocket->getScore() + 100);
				_em->removeBoat(j);
				_rocket->getRocketLauncher()->addBullet();
				break;
			}
		}
	}

	for (int i = 0; i < _rocket->getRocketLauncher()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getHeli().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getRocketLauncher()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getHeli()[j]->getRect(), 10, 40)))
			{
				_rocket->removeRocketLauncher(i);
				_rocketLauncherEffect->show(rc);
				_helicopterDieEffect->show(rc);
				_rocket->setScore(_rocket->getScore() + 1000);
				_em->removeHeli(j);
				_rocket->getRocketLauncher()->addBullet();
				break;
			}
		}
	}
	//적 공격
	for (int i = 0; i < _em->getMinions().size(); i++)
	{
		for (int j = 0; j < _em->getMinions()[i]->getMissile()->getBullet().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_em->getMinions()[i]->getMissile()->getBullet()[j].rc,
				&CollisionAreaResizing(_rocket->getRect(), 0, 30)))
			{
				_rocket->hitDamage(0.1);
				_playerEffect->show(_rocket->getRect());
				_em->getMinions()[i]->removeMissile(j);
			}
		}
	}

	for (int i = 0; i < _em->getBoat().size(); i++)
	{
		for (int j = 0; j < _em->getBoat()[i]->getMissile()->getBullet().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_em->getBoat()[i]->getMissile()->getBullet()[j].rc,
				&CollisionAreaResizing(_rocket->getRect(), 25, 30)))
			{
				_rocket->hitDamage(0.3);
				_playerEffect->show(rc);
				_em->getBoat()[i]->getMissile()->removeBullet(j);
			}
		}
	}

	for (int i = 0; i < _em->getHeli().size(); i++)
	{
		for (int j = 0; j < _em->getHeli()[i]->getMissile()->getBullet().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_em->getHeli()[i]->getMissile()->getBullet()[j].rc,
				&CollisionAreaResizing(_rocket->getRect(), 25, 30)))
			{
				_rocket->hitDamage(0.5);
				_playerEffect->show(rc);
				_em->getHeli()[i]->getMissile()->removeBullet(j);
			}
		}
	}

	if (_rocket->getCurrentHp() < 0)
	{
		_currentScean = _gameEndScene;
		_gameEndScene->setSelectImage(1);
		_sceanNum = 2;
	}
	
	for (int i = 0; i < _rocket->getMissile()->getBullet().size(); i++)
	{
		
		RECT _rcTemp;
		if (IntersectRect(&_rcTemp, &rc, &_rocket->getMissile()->getBullet()[i].rc))
		{
			_rocket->removeMissile(i);
			_missileEffect->show(_rcTemp);
			break;
		}
		
	}
}