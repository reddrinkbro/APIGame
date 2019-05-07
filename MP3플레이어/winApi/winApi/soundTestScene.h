#pragma once
#include "gameNode.h"
#include "progressBar.h"
class soundTestScene : public gameNode
{
private:
	RECT _rc[5];
	progressBar* _progressBar;
	progressBar* _volumeBar;
	int _num;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void play(void);
	void pause(void);
	void resume(void);
	void next(void);
	void previous(void);
	void setPosition(void);
	void setVolume(void);
	void soundChange(void);
	soundTestScene() {}
	~soundTestScene() {}
};

