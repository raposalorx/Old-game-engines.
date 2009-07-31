#ifndef ROGUEMUD_STATE_GAME_H
#define ROGUEMUD_STATE_GAME_H

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include "luaenv.h"
#include "ns_game.h"
#include "ns_state_game.h"
#include "state.h"

using namespace ns_game;
using namespace ns_state_game;

/**
**/

class State_Game : public State
{
	public:
		State_Game();
		~State_Game();

		void Event();
		bool Step();
		void Draw();
	protected:
	private:
};

#endif
