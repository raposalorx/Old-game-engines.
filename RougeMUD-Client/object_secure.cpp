#include "object_secure.h"

Object_Secure::Object_Secure()
{
}

Object_Secure::Object_Secure(int new_table)
{
	PopulateTable(LuaState, new_table);
	PopulateRegistry(LuaState);
}

Object_Secure::~Object_Secure()
{
}

void Object_Secure::PopulateTable(lua_State *L, int new_table)
{
	Object_Region::PopulateTable(LuaState, new_table);
}

void Object_Secure::PopulateRegistry(lua_State *L)
{
	Object_Region::PopulateRegistry(LuaState);
}
