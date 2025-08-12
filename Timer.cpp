#include "Timer.h"
#include "Common.h"

Timer::Timer()
	: m_StartTicks{0}		
{
}

void Timer::start()
{
	m_StartTicks = SDL_GetTicks();
}

Uint64 Timer::getTicks()
{
    return SDL_GetTicks() - m_StartTicks;
}