#ifndef ROGUEMUD_GAME_H
#define ROGUEMUD_GAME_H

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL_net.h>

#include <string>
#include <vector>

#include "ns_game.h"
#include "being.h"

using namespace std;
using namespace ns_game;

/**
**/

class Game
{
	public:
		Game();
		~Game();
		bool LoopEvents();
		bool LoopLogic();
	protected:
	private:
		vector<Being> beingDB;
		vector<int> inActiveList;// recycling
};

#endif
