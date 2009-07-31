#include "object.h"

Object::Object()
{
}

Object::Object(int new_table)
{
	PopulateTable(LuaState, new_table);
	PopulateRegistry(LuaState);
}

Object::~Object()
{
}

void Object::PopulateTable(lua_State *L, int new_table)
{
}

void Object::PopulateRegistry(lua_State *L)
{
	// Create an entry in the Lua Registry for this new object
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushlightuserdata(L, this);					// +1     2
	lua_newtable(L);								// +1     3
	lua_settable(L, -3);							//    -2  1
	lua_pop(L, 1);									//    -1  0
}

/// Returns the pointer to the object specified by table or string reference
int GetObject(int object)
{
	lua_State *L = LuaState;
	/// TODO: make it also work by string reference

	// Grab the object's pointer
	if (lua_istable(L, 1))
	{
		lua_pushnumber(L, 0);			// +1     1
		lua_gettable(L, 1);				// +1     2
		return lua_gettop(L);			//    -2  0
	}
	return NULL;
}
