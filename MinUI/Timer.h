////////////////////////////////////////////////////////////////////////////////
// Timer.h
// -----------------------------------------------------------------------------
// Simple timer class.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <unistd.h>
#include <sys/time.h>

namespace MinUI
{
class Timer
{
    private:

	struct timeval t0, t1;

    public:

	Timer();

	void reset();

	float getTimeMS();
};
}

