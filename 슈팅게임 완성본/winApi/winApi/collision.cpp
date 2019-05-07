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
				_enemyEffect->show(_em->getMinions()[j]->getRect());
				_em->removeMinion(j);
				_rocket->setScore(_rocket->getScore() + 1);
				break;
			}
		}
	}
	for (int i = 0; i < _rocket->getMissile()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_rocket->getMissile()->getBullet()[i].rc,
			&CollisionAreaResizing(_em->getBoss()->getRect(), 10, 40)) && _em->getBoss()->getIsAppear())
		{
			_rocket->removeMissile(i);
			_em->getBoss()->hitdamage(1);
			if (_em->getBoss()->getCurrentHp() < 0)
			{
				_bossDieEffect->show(_em->getBoss()->getRect());
			}
			else
			{
				_bossHitEffect->show(rc);
			}
			break;
		}
	}
	//플레이어 공격,에너지볼일때
	for (int i = 0; i < _rocket->getEnegyBall()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getEnegyBall()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 0, 30)))
			{
				_rocket->removeEnegyBall(i);
				_enemyEnegyBallEffect->show(_em->getMinions()[j]->getRect());
				_em->removeMinion(j);
				_rocket->setScore(_rocket->getScore() + 1);
				break;
			}
		}
	}
	for (int i = 0; i < _rocket->getEnegyBall()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_rocket->getEnegyBall()->getBullet()[i].rc,
			&CollisionAreaResizing(_em->getBoss()->getRect(), 10, 40)) && _em->getBoss()->getIsAppear())
		{
			_rocket->removeEnegyBall(i);
			_em->getBoss()->hitdamage(3);
			if (_em->getBoss()->getCurrentHp() < 0)
			{
				_bossDieEffect->show(_em->getBoss()->getRect());
			}
			else
			{
				_enemyEnegyBallEffect->show(rc);
			}
			break;
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

	for (int i = 0; i < _em->getBoss()->getMissile()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_em->getBoss()->getMissile()->getBullet()[i].rc,
			&CollisionAreaResizing(_rocket->getRect(), 25, 30)))
		{
			_rocket->hitDamage(0.3);
			_playerEffect->show(rc);
			_em->getBoss()->getMissile()->removeBullet(i);
		}
	}
	if (_rocket->getCurrentHp() < 0)
	{
		_currentScean = _gameEndScene;
		_gameEndScene->setSelectImage(1);
		_sceanNum = 2;
	}
	else if (_em->getBoss()->getCurrentHp() < 0)
	{
		_currentScean = _gameEndScene;
		_gameEndScene->setSelectImage(0);
		_sceanNum = 2;
	}

	//소용돌이
	for (int i = 0; i < _objectWind->getvRect().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_objectWind->getvRect()[i],
			&CollisionAreaResizing(_rocket->getRect(), 25, 30)))
		{
			_rocket->setWindHit(true);
			break;
		}
		else
		{
			_rocket->setWindHit(false);
		}
	}
}