#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"

HRESULT effectManager::init(void)
{
	return S_OK;
}

void effectManager::release(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;
	vIter = _vArrTotalEffect.begin();
	for(vIter; vIter !=_vArrTotalEffect.end() ; ++vIter)
	{
		mIter = vIter->begin();
		for(mIter; mIter != vIter->end();)
		{
			if(mIter->second.size() != 0)
			{
				iterEffects vArrIter = mIter->second.begin();
				for(vArrIter; vArrIter != mIter->second.end();)
				{
					(*vArrIter)->release();
					SAFE_DELETE(*vArrIter);
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else
			{
				++mIter;
			}
		}
	}
	_vArrTotalEffect.clear();
}

void effectManager::update(float elapsedTime)
{
	iterTotalEffect vIter;
	iterEffect mIter;
	for (vIter = _vArrTotalEffect.begin(); vIter != _vArrTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for(vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update(elapsedTime);
			}
		}
	}
}

void effectManager::render(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;
	for (vIter = _vArrTotalEffect.begin(); vIter != _vArrTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}
}

void effectManager::addEffect(string effectName, const char* imageName, int imagewidth, int imageHeights, int effectWidth
	, int effectHeight, int fps, int buffer)
{

	image* img;
	arrEffects vEffectBuffer;
	arrEffect mArrEffect;
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else
	{
		img = IMAGEMANAGER->addImage(imageName, imageName, imagewidth, imageHeights, true, RGB(255, 0, 255));
	}
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps);
	}
	mArrEffect.insert(make_pair(effectName, vEffectBuffer));
	_vArrTotalEffect.push_back(mArrEffect);
}

void effectManager::play(string effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect mIter;
	for(vIter = _vArrTotalEffect.begin(); vIter != _vArrTotalEffect.end(); ++vIter)
	{
		for(mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if(effectName != mIter->first)break;
			iterEffects vArrIter;
			for(vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if((*vArrIter)->getIsRunning())continue;
				(*vArrIter)->start(x,y);
				return;
			}
		}
	}
}
