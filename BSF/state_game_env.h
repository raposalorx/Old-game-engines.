#ifndef STATE_GAME_ENV_H
#define STATE_GAME_ENV_H

#include <vector>

#include "radixtrie.h"
#include "state_env.h"

using namespace std;
using namespace state_env;

class Object;
class Object_Unit;

namespace state_game_env
{
	extern vector<Object*> objectDB;
	extern vector<Object_Unit*> unitDB;
	extern RadixTrie tree_objects;
}

#endif
