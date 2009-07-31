#include "ns_state_game.h"

lua_State *ns_state_game::LuaState;
Object_Region *ns_state_game::region_global;
vector<Object_Surface*> ns_state_game::obj_surfaceDB[1];
