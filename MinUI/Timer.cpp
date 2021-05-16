#include "Timer.h"

namespace MinUI
{

Timer::Timer()
{
	reset();
}

void Timer::reset()
{
	gettimeofday(&t0, NULL);
}

float Timer::getTimeMS()
{
	gettimeofday(&t1, NULL);
	float time =
	        (t1.tv_sec - t0.tv_sec) * 1e3 +
	        (t1.tv_usec - t0.tv_usec) / 1e3;
	return time;
}

}

