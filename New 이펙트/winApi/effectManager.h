#pragma once
#include "singletonBase.h"

class effect;
class effectManager : public singletonBase<effectManager>
{
private:
	typedef vector<effect*> arrEffects;
	typedef vector<effect*>::iterator iterEffects;
	typedef map <string, arrEffects> arrEffect;
	typedef map<string,arrEffects>::iterator iterEffect;
	typedef vector<map<string, arrEffects>> arrTotalEffect;
	typedef vector<map<string, arrEffects>>::iterator iterTotalEffect;
private:
	arrTotalEffect _vArrTotalEffect;
public:
	HRESULT init(void);
	void release(void);
	void update(float elapsedTime);
	void render(void);

	void addEffect(string effectName , const char* imageName, int imagewidth, int imageHeights, int effectWidth
	,int effectHeight, int fps, int buffer);
	void play(string effectName,int x, int y);
	effectManager() {}
	~effectManager() {}
};

