#pragma once
#include "gameNode.h"
struct tagBullet
{
	image* _image;
	RECT _rc;
	float _x, _y;
	float _angle;
	float _speed;
	float _time;
	int _probeY;
};
class tankBullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _bulletMax;
	float _range;
public:
	HRESULT init(float range, int bulletMax);
	void release(void);
	void update(void);
	void render(void);
	void fire(float x, float y,float angle);
	void move(void);
	void draw(void);
	void remove(int arrNum);
	vector<tagBullet> getbullet(void) { return _vBullet; }
	tankBullet(){}
	~tankBullet(){}
};

