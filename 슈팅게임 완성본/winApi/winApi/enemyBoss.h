#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"
class enemyBoss : public gameNode
{
private:
	image* _bossImage;
	bossProgressBar* _progressBar;
	bossBullet* _bossBullet;
	RECT _rc;
	float _x, _y;
	float _currentHp;
	float _maxHp;
	bool _isAppear;
public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);

	bool getIsAppear(void) { return _isAppear; }
	void setIsAppear(bool isAppear) { _isAppear = isAppear; }
	void hitdamage(int damage)
	{
		if (_currentHp < 0)
		{
			_currentHp = 0;
			return;
		}
		_currentHp -= damage;
	}
	RECT getRect(void) { return _rc; }
	float getCurrentHp(void) { return _currentHp; }
	bossBullet* getMissile(void) { return _bossBullet; }
	enemyBoss(){}
	~enemyBoss(){}
};

