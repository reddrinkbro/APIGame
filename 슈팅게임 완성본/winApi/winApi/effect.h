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

class enemyEnegyBallEffect : public gameNode
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

	enemyEnegyBallEffect() {}
	~enemyEnegyBallEffect() {}
};

class bossHitEffect : public gameNode
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

	bossHitEffect() {}
	~bossHitEffect() {}
};

class bossDieEffect : public gameNode
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

	bossDieEffect() {}
	~bossDieEffect() {}
};