#include "state_game_env.h"

vector<Object*> state_game_env::objectDB;
vector<Object_Unit*> state_game_env::unitDB;
RadixTrie state_game_env::tree_objects;
