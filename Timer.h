#ifndef TIMER_H
#define TIMER_H
#include "Common.h"

class Timer
{
public:
	Timer();

	void start();

	Uint64 getTicks();
private:
	Uint64 m_StartTicks{0};
	Uint64 m_CurrentTicks{0};
};

#endif