#pragma once
#include "gameNode.h"

class effectTestScene : public gameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	effectTestScene() {}
	~effectTestScene() {}
};

