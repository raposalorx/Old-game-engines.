#ifndef ROGUEMUD_TIMER_H
#define ROGUEMUD_TIMER_H

#include <SDL.h>

class Timer
{
	public:
		Timer();
		void Start();
		void Stop();
		int GetTime();
		bool IsRunning();
	protected:
	private:
		int begin_time;
		bool running;
};

#endif
