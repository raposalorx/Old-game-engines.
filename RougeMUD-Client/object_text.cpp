#include "object_text.h"

Object_Text::Object_Text()
{
}

Object_Text::Object_Text(int new_table)
{
	PopulateTable(LuaState, new_table);
	PopulateRegistry(LuaState);
}

Object_Text::~Object_Text()
{
}

void Object_Text::PopulateTable(lua_State *L, int new_table)
{
	Object_Surface::PopulateTable(LuaState, new_table);
}

void Object_Text::PopulateRegistry(lua_State *L)
{
	Object_Surface::PopulateRegistry(LuaState);
}

void Object_Text::Draw()
{
	// return surface;
}
