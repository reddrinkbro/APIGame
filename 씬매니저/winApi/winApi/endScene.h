#pragma once
#include "gameNode.h"
#include "player.h"
class endScene : public gameNode
{
private:
	image* _image;
	image* _imageDie;
	player* _player;
	float _x, _y;
	float _time;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void nextScene(void);
	endScene(){}
	~endScene(){}
};

