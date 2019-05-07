#include "stdafx.h"
#include "animation.h"

animation::animation() : _frameNum(0),
						 _frameWidth(0),
						 _frameHeight(0),
						 _frameNumWidth(0),
						 _frameNumHeight(0),
						 _loop(FALSE),
						 _frameUpdateSec(0),
						 _elapsedSec(0),
						 _nowPlayIdx(0),
						 _isPlay(FALSE),
						 _isSectionEnd(FALSE),
						 count(0)
{
}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//���� ������ ��
	_frameWidth = frameW;
	_frameNumWidth = totalW / _frameWidth;

	//���� ������ ��
	_frameHeight = frameH;
	_frameNumHeight = totalH / _frameHeight;

	//�� ������ �� ���
	_frameNum = _frameNumWidth * _frameNumHeight;

	//������ ��ġ ����Ʈ ����
	_frameList.clear();
	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//������ ��ġ ����Ʈ�� �߰�
			_frameList.push_back(framePos);
		}
	}

	//���� �⺻ ���������� ����
	setDefPlayFrame();

	return S_OK;
}

void animation::release(void)
{
}

//�⺻ ������ ����
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//���� ������
	_loop = loop;

	_playList.clear();

	//�ٽ� ���ƿ���?
	if (reverse)
	{
		//����?
		if (_loop)
		{
			//���� ������
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//�ö� ������
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//���� ������
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//�ö� ������
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	//��
	else 
	{
		//���� ������
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

//���ϴ� �����Ӹ� ���
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	_loop = loop;
	_isPlay = true;
	
	if (vInt.size() <= arrLen)
	{
		vInt.push_back(playArr);
	}
	/*int *numArr = new int[arrLen];
	*numArr = *playArr;*/
	for (int i = 0; i < _playList.size(); i++)
	{
		if (loop)
		{
			if (i == *playArr && !_isSectionEnd)
			{
				count++;
				_nowPlayIdx = _playList[i];
			}
			else if (vInt.size() == arrLen)
			{
				_isSectionEnd = true;
				count--;
				_nowPlayIdx = *vInt[count];
				break;
				if (count < 0)
				{
					_isSectionEnd = false;
				}
			}
		}
		else
		{
			if (i == *playArr && !_isSectionEnd)
			{
				count++;
				_nowPlayIdx = _playList[i];
			}
		}
	}
}

//������ �߶� ���
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_loop = loop;
	_isPlay = true;
	if (reverse)
	{
		if (_loop)
		{

			if (_nowPlayIdx >= end)
			{
				_isSectionEnd = true;
			}
			else if (_nowPlayIdx < start)
			{
				_nowPlayIdx = start;
				_isSectionEnd = false;
			}
		}
		else
		{
			if (_nowPlayIdx >= end)
			{
				_isSectionEnd = true;
			}
			else if (_nowPlayIdx < start)
			{
				_nowPlayIdx = start;
				_isPlay = false;
			}
		}
	}
	else
	{
		if (_nowPlayIdx >= end)
		{
			_nowPlayIdx = start;
		}
	}
	if (_isSectionEnd)
	{
		_nowPlayIdx -= 2;
	}
}

//�ʴ� ������ ���� Ƚ��
void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 0.0166667 / framePerSec ;
}

//������ ������Ʈ
void animation::frameUpdate(float elpasedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elpasedTime;

		//������ ������Ʈ �ð��� �Ǿ�����
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIdx++;
			if (_nowPlayIdx == _playList.size())
			{				
				if (_loop)
				{
					_nowPlayIdx = 0;
				}
				else
				{
					_nowPlayIdx--;
					_isPlay = false;
				}
			}
		}
	}
}

void animation::start(void)
{
	_isPlay = true;
	if(!_isSectionEnd) _nowPlayIdx = 0;
}

void animation::stop(void)
{
	_isPlay = false;
	_nowPlayIdx = 0;
}

void animation::pause(void)
{
	_isPlay = false;
}

void animation::resume(void)
{
	_isPlay = TRUE;
}