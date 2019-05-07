#pragma once
#include "gameNode.h"

struct tagEffect
{
	image* img;
	RECT rc;
	float x;
	float y;
	int count;
};

class playerEffect : public gameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	playerEffect() {}
	~playerEffect() {}
};

class enemyEffect : public gameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	enemyEffect() {}
	~enemyEffect() {}
};

class rocketLauncherEffect : public gameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	rocketLauncherEffect() {}
	~rocketLauncherEffect() {}
};

class missileEffect : public gameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	missileEffect() {}
	~missileEffect() {}
};

class helicopterDieEffect : public gameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	helicopterDieEffect() {}
	~helicopterDieEffect() {}
};