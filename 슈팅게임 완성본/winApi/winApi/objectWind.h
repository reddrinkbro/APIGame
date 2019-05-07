#pragma once
#include "gameNode.h"
class objectWind : public gameNode
{
private:
	image* _image;
	int _count;
	RECT _rc;
	vector<RECT> _vRect;
	vector<RECT>::iterator _viRect;
public:
	vector<RECT> getvRect(void) { return _vRect; }
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	objectWind(){}
	~objectWind(){}
};

