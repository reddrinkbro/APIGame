#pragma once
#include "gameNode.h"
class gameEndScene : public gameNode
{
	image* _winImage;
	image* _loseImage;
	int _selectImage;
public:
	void setSelectImage(int selectImage) { _selectImage = selectImage; }
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	gameEndScene(){}
	~gameEndScene(){}
};

