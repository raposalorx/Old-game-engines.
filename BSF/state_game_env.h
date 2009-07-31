#ifndef STATE_GAME_ENV_H
#define STATE_GAME_ENV_H

#include <vector>

#include "radixtrie.h"
#include "texture.h"

using namespace std;

class Object;
class Object_Unit;

namespace state_game_env
{
	extern vector<Texture> textureDB;
	extern vector<Object*> objectDB;
	extern vector<Object_Unit*> unitDB;
	extern RadixTrie tree_textures, tree_objects;
	extern int mouse_x, mouse_y;
	extern int screen_w, screen_h;
}

#endif
