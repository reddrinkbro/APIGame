#pragma once
#include "gameNode.h"
class startScene : public gameNode
{
private:
	image* _image;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	startScene(){}
	~startScene(){}
};

