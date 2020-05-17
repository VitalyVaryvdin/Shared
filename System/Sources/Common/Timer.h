#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

class Timer
{
public:
	enum
	{
		Sec,
		MiliSec
	};

	static void		Start();
	static void		Stop();

	static double	GetTime(IN int Mode = MiliSec);
private:
	static long		mStart;
	static long		mEnd;

	static double	mSeconds;
	static double	mMiliseconds;
};