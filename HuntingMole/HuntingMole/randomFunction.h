#pragma once

#include "singletonBase.h"
#include <time.h>

//======================
//	## randomFunction ## 
//======================
class randomFunction : public singletonBase <randomFunction>
{
public:
	randomFunction()
	{
		srand(time(NULL));
	}
	~randomFunction() {}

	inline int getInt(int num) { return rand() % num; }

	//주의사항 -> 0이 나오면 터진다
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};

