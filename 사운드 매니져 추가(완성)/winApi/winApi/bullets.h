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

//�������� ���� �Ѿ� (�򶧸��� ����� ����)
class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	int _bulletMax;
	float _range;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);
	vector<tagBullet> getBullet(void) { return _vBullet; }

	bullet() {}
	virtual ~bullet() {}
};

//�迭ó�� �̸� �����صΰ� �߻�
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

//�򶧸��� ����� ����
//�޸� ���̵�
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



