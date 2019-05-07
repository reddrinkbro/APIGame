#pragma once
#include "gamenode.h"
#include "animation.h"

class animationTest : public gameNode
{
private:
	image* _image;
	animation* _animation0;
	int count;
	int arr[5];
	int* parr;
		
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	animationTest(void) {}
	~animationTest(void) {}
};
