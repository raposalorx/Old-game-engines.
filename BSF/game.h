#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_opengl.h>

#include "state_game.h"
#include "state_menu.h"

class Game
{
	public:
		Game();
		~Game();

		bool Init();
		void Event();
		void Logic();
		void Render();
		bool ChangeState();
	protected:
	private:
		State* game_state;
		Enum_State state_current;
};

#endif
