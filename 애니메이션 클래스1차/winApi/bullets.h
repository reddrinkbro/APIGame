#pragma once
#include "gameNode.h"

struct tagBullet
{
	image* img;
	RECT rc;
	float x;
	float y;
	float fireX, fireY;
	float angle;
	float speed;
	int radius;
	int count;
	bool fire;
};

//배열처럼 미리 장전해두고 발사
class missile : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	missile() {}
	~missile() {}
};

//쏠때마다 만들고 삭제
//메모리 핵이득
class missileM1 : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	void removeBullet(int arrNum);

	missileM1() {}
	~missileM1() {}
};

class beam : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	beam() {}
	~beam() {}
};



