#include "stdafx.h"
#include "secondScene.h"


void secondScene::shopWindow(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (PtInRect(&_rc[i], _ptMouse))
		{
			if (_player->getMoney() > 0)
			{
				_player->getItemWindow()->pushItem(i);
				if (i == 0)
				{
					for (int j = 0; j < _player->getItemWindow()->gethpVec().size(); j++)
					{
						_player->setMoney(_player->getMoney() - _player->getItemWindow()->gethpVec()[j]->getCost());
						break;
					}
				}
				if (i == 1)
				{
					for (int j = 0; j < _player->getItemWindow()->getSVec().size(); j++)
					{
						_player->setMoney(_player->getMoney() - _player->getItemWindow()->getSVec()[j]->getCost());
						break;
					}
				}
				if (i == 2)
				{
					for (int j = 0; j < _player->getItemWindow()->getSwordVec().size(); j++)
					{
						_player->setMoney(_player->getMoney() - _player->getItemWindow()->getSwordVec()[j]->getCost());
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < _player->getItemWindow()->gethpVec().size(); i++)
	{
		if (PtInRect(&_player->getItemWindow()->gethpVec()[i]->getRect(), _ptMouse))
		{
			_player->setMoney(_player->getMoney() + _player->getItemWindow()->gethpVec()[i]->getCost());
			_player->getItemWindow()->usingItem(0);
			break;
		}
	}
	for (int i = 0; i < _player->getItemWindow()->getSVec().size(); i++)
	{
		if (PtInRect(&_player->getItemWindow()->getSVec()[i]->getRect(), _ptMouse))
		{
			_player->setMoney(_player->getMoney() + _player->getItemWindow()->getSVec()[i]->getCost());
			_player->getItemWindow()->usingItem(1);
			break;
		}
	}
	for (int i = 0; i < _player->getItemWindow()->getSwordVec().size(); i++)
	{
		if (PtInRect(&_player->getItemWindow()->getSwordVec()[i]->getRect(), _ptMouse))
		{
			_player->setMoney(_player->getMoney() + _player->getItemWindow()->getSwordVec()[i]->getCost());
			_player->getItemWindow()->usingItem(2);
			break;
		}
	}
}
