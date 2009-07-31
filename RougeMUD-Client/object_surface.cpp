#include "object_surface.h"

Object_Surface::Object_Surface()
{
	obj_surfaceDB[LAYER_NORMAL].push_back(this);
}

Object_Surface::Object_Surface(int new_table)
{
	// surface = imageDB[0];
	obj_surfaceDB[LAYER_NORMAL].push_back(this);
	PopulateTable(LuaState, new_table);
	PopulateRegistry(LuaState);
}

Object_Surface::~Object_Surface()
{
	// SDL_FreeSurface(screen);
}

void Object_Surface::PopulateTable(lua_State *L, int new_table)
{
	Object_Region::PopulateTable(LuaState, new_table);
}

void Object_Surface::PopulateRegistry(lua_State *L)
{
	Object_Region::PopulateRegistry(LuaState);
}

void Object_Surface::Draw()
{
	
}
