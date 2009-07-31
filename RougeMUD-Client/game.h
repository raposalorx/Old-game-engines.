#ifndef ROGUEMUD_GAME_H
#define ROGUEMUD_GAME_H

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL.h>
#include <SDL_net.h>
#include <SDL_opengl.h>

#include <fstream>
#include <string>
#include <vector>

#include "ns_game.h"
#include "timer.h"
#include "state.h"
#include "state_game.h"
#include "state_login.h"
#include "texture.h"
#include "being.h"

using namespace std;
using namespace ns_game;

/**
	The Game class encompasses the entire game, all other files are included from here
**/

class Game
{
	public:
		Game();
		~Game();
		void LoopEvents();
		bool LoopLogic();
		bool ChangeState();
		void LoopRender();
	protected:
	private:
		State* game_state;
};

class IMG_EXCEPTION: public exception
{
	virtual const char* what() const throw();
}static IMG_LOAD_EXCEPTION;

#endif
