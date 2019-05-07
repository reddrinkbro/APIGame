#pragma once
#include "singletonbase.h"
//fmod.hpp 추가
#include "inc/fmod.hpp"
//lib 링크
#pragma comment (lib, "lib/fmodex_vc.lib")

//사운드 갯수만큼 설정
#define SOUND_BUFFER 7 
//여분의 채널 갯수 (버퍼)
#define EXTRA_SOUND_CHANNEL 7
//총 사운드 갯수
#define TOTAL_SOUND_CHANNEL (SOUND_BUFFER + EXTRA_SOUND_CHANNEL)

using namespace FMOD;

class soundManager : public singletonBase <soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;
	vector <string> _soundName;
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;
	int _index;
	float _volume;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
		
	void addSound(string keyName, string soundName,
		bool background, bool loop);
		
	void play(string keyName , float volume);	
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);
	float getVolume(string keyName);
	void setVolume(string keyName , float volume);
	void next(void);
	void previous(void);
	unsigned int soundLength(string keyName);
	unsigned int soundPosition(string keyName);
	void soundSetPosition(string keyName, unsigned int currentPosition);
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);
	
	vector <string> getSoundName(void) { return _soundName; }
	soundManager();
	~soundManager() {}
};