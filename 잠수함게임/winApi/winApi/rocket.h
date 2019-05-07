#pragma once
#include "gameNode.h"
#include "flame.h"
#include "bullets.h"
#include "progressBar.h"

#define ROCKETSPEED 2.0f

enum weapon
{
	MISSILE, MISSILE2
};

class rocket : public gameNode
{
private:
	image* _image;
	flame* _flame;
	missileM1* _missile;
	rocketLauncher* _rocketLauncher;
	progressBar* _hpBar;

	weapon _setWeapon;
	RECT _rc;
	int _currentFrame;
	int _score;

	bool _windHit;

	float _x, _y;
	float _currentHp;
	float _maxHp;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void removeMissile(int arrNum);
	void removeRocketLauncher(int arrNum);

	missileM1* getMissile(void) { return _missile; }
	rocketLauncher* getRocketLauncher(void) { return _rocketLauncher; }
	RECT getRect(void) { return _rc; }
	bool getWindHit(void) { return _windHit; }
	void setWindHit(bool windHit) { _windHit = windHit; }
	int getScore(void) { return _score; }
	void setScore(int score) { _score = score; }

	void hitDamage(float damage)
	{
		if (_currentHp < 0)
		{
			_currentHp = 0;
			return;
		}
		_currentHp -= damage;
	}
	float getCurrentHp(void) { return _currentHp; }
	rocket() {}
	~rocket() {}
};

