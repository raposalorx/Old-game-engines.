#include "state_env.h"

vector<Texture> state_env::textureDB;
RadixTrie state_env::tree_textures;
int state_env::mouse_x, state_env::mouse_y;
double state_env::screen_w, state_env::screen_h, state_env::screen_x, state_env::screen_y;
double state_env::game_w, state_env::game_h;
