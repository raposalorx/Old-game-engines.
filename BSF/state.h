#ifndef STATE_H
#define STATE_H

#include <SDL.h>
#include <SDL_opengl.h>

enum Enum_State
{
	STATE_NULL,
	STATE_EXIT,
	STATE_MENU,
	STATE_GAME
};

class State
{
	public:
		State() {state_next = STATE_NULL;}
		virtual ~State() {}

		virtual void Event() {}
		virtual void Logic() {}
		virtual void Render() {}
		virtual Enum_State ChangeState() {return STATE_NULL;}
	protected:
		Enum_State state_next;
	private:
};

#endif
