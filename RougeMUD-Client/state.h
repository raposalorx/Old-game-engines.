#ifndef ROGUEMUD_STATE_H
#define ROGUEMUD_STATE_H

#include <SDL.h>

/**
	The State class is used as a parent class; its derivatives are used as game states, such as the login screen, or the game itself
**/

class State
{
	public:
		State();
		virtual ~State();

		virtual void Event();
		virtual bool Step();
		virtual void Draw();
	protected:
	private:
};

#endif
