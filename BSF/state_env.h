#ifndef STATE_ENV_H
#define STATE_ENV_H

#include <vector>

#include "texture.h"
#include "radixtrie.h"

using namespace std;

namespace state_env
{
	extern vector<Texture> textureDB;
	extern RadixTrie tree_textures;
	extern int mouse_x, mouse_y;
	extern double screen_w, screen_h, screen_x, screen_y;
	extern double game_w, game_h;
}

#endif
