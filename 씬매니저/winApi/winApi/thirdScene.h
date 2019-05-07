#pragma once
#include "gameNode.h"
#include "buccanary.h"
#include "player.h"
#include "popUp.h"
class thirdScene : public gameNode
{
private:
	image* _image;
	buccanary* _buccanary;
	player* _player;
	popUp* _popUp;
	float _x, _y;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void nextScene(void);
	void popUpWindow(void);
	thirdScene(){}
	~thirdScene(){}
};

