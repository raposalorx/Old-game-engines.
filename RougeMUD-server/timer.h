#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

/**
**/

class Timer
{
	public:
		Timer();
		void Start();
		void Stop();
		int GetTime();
		bool IsRunning();
	private:
		int begin_time;
		bool running;
};

#endif
