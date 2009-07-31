#ifndef ROGUEMUD_LUAENV_H
#define ROGUEMUD_LUAENV_H

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <vector>

#include "ns_state_game.h"
#include "object_button.h"
#include "object_globalregion.h"
#include "object_image.h"
#include "object_text.h"
#include "object_worldview.h"

using namespace ns_state_game;

void init_lua();
void uninit_lua();
void SendEvent(const char* event);
void ResolveRegionAbsolutePositions(Object *object);

int L_Print(lua_State *L);
int L_CreateFrame(lua_State *L);
int L_DebugRegTable(lua_State *L);

#endif
