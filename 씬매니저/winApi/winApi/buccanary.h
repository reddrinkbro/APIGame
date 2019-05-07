#pragma once
#include "gameNode.h"
class buccanary : public gameNode
{
private:
	image* _image;
	RECT _rc;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	RECT getRect(void) { return _rc; }
	buccanary(){}
	~buccanary(){}
};

