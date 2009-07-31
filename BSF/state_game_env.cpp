#include "state_game_env.h"

vector<Texture> state_game_env::textureDB;
vector<Object*> state_game_env::objectDB;
vector<Object_Unit*> state_game_env::unitDB;
RadixTrie state_game_env::tree_textures, state_game_env::tree_objects;
int state_game_env::mouse_x, state_game_env::mouse_y;
int state_game_env::screen_w, state_game_env::screen_h;
