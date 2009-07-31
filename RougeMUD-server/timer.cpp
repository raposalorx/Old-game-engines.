#include "timer.h"

Timer::Timer()
{
	begin_time = 0;
	running = false;
}

void Timer::Start()
{
	begin_time = SDL_GetTicks();
	running = true;
}

void Timer::Stop()
{
	if(running)
	{
		begin_time = 0;
		running = false;
	}
}

int Timer::GetTime()
{
	if(running)
		return SDL_GetTicks() - begin_time;
	else
		return 0;
}

bool Timer::IsRunning()
{
	return running;
}
