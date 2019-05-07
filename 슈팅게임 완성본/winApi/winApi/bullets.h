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
	int bulletNum;
};

//ΩÚ∂ß∏∂¥Ÿ ∏∏µÈ∞Ì ªË¡¶
//∏ﬁ∏∏Æ «Ÿ¿ÃµÊ
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

class enegyBall : public gameNode
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

	enegyBall() {}
	~enegyBall() {}
};

class enemyBullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	float _time;
	int _bulletMax;

public:
	HRESULT init(int bulletMax);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y , float angle);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	void removeBullet(int arrNum);

	enemyBullet() {}
	~enemyBullet() {}
};

class bossBullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	float _time;
	int _bulletMax;
public:
	HRESULT init(int bulletMax);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	void removeBullet(int arrNum);

	bossBullet() {}
	~bossBullet() {}
};


