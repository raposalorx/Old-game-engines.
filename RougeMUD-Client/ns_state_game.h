#ifndef ROGUEMUD_NS_STATE_GAME_H
#define ROGUEMUD_NS_STATE_GAME_H

#include <vector>

class lua_State;
class Object_Surface;
class Object_Region;

using namespace std;

/**
	The game namespace is used to statically store information introduced by state_game.h/cpp
**/

namespace ns_state_game
{
	extern lua_State *LuaState;
	extern Object_Region *region_global;
	extern vector<Object_Surface*> obj_surfaceDB[1];
}

// Definitions for referring to the layers by name in C++ code
// Layers are drawn from lowest to highest, so this list will often be re-ordered
// Preprocessor definitions are used to make the reordering simpler for us, with no runtime cost
#define LAYER_NORMAL 0

#endif
