#include "stdafx.h"
#include "mainGame.h"

void mainGame::sceneMove()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_player->getRect().left > _startScene->getRect().left && _player->getRect().right < _startScene->getRect().right && _gameNode == _startScene)
		{
			_gameNode = _secondScene;
			_player->characterMapMove(_secondScene->getRect().left, _secondScene->getRect().top);
		}
		else if (_player->getRect().left > _secondScene->getRect().left && _player->getRect().right < _secondScene->getRect().right && _gameNode == _secondScene)
		{
			_gameNode = _startScene;
			_player->characterMapMove(_startScene->getRect().left, _startScene->getRect().top);
		}
	}
}