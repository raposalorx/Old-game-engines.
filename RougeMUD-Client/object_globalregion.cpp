#include "object_globalregion.h"

Object_GlobalRegion::Object_GlobalRegion()
{
	x = 0;
	y = 0;
	width = WIDTH;
	height = HEIGHT;
}

Object_GlobalRegion::Object_GlobalRegion(int new_table)
{
	PopulateTable(LuaState, new_table);
	PopulateRegistry(LuaState);
}

Object_GlobalRegion::~Object_GlobalRegion()
{
}

void Object_GlobalRegion::PopulateTable(lua_State *L, int new_table)
{
	lua_pushstring(L, "Show");				// +1     1
	lua_pushcfunction(L, L_Show);			// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "Hide");				// +1     1
	lua_pushcfunction(L, L_Hide);			// +1     2
	lua_settable(L, new_table);				//    -2  0
/*	lua_pushstring(L, "SetPoint");			// +1     1
	lua_pushcfunction(L, L_SetPoint);		// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "DelPoint");			// +1     1
	lua_pushcfunction(L, L_GetPoint);		// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "GetPoint");			// +1     1
	lua_pushcfunction(L, L_GetPoint);		// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "GetPointCount");		// +1     1
	lua_pushcfunction(L, L_GetPointCount);	// +1     2
	lua_settable(L, new_table);				//    -2  0*/
}

void Object_GlobalRegion::PopulateRegistry(lua_State *L)
{
	Object::PopulateRegistry(L);

/*	int top = lua_gettop(L);

	// Registry table
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushlightuserdata(L, this);					// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	int reg_table = lua_gettop(L);
	// Point table
	lua_pushstring(L, "POINT");					// +1     4
	lua_newtable(L);							// +1     5
		// Point count field
		lua_pushnumber(L, 0);					// +1     6
		lua_pushnumber(L, 5);					// +1     7
		lua_settable(L, -3);					//    -2  5
		// TOP LEFT point
		lua_pushnumber(L, 1);					// +1     6
		lua_newtable(L);						// +1     7
			lua_pushstring(L, "TOPLEFT");		// +1     8
			lua_setfield(L, -2, "NAME");		//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "X");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "Y");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "ANCHORS");		//    -1  7
		lua_settable(L, -3);					//    -2  5
		// TOP RIGHT point
		lua_pushnumber(L, 2);					// +1     6
		lua_newtable(L);						// +1     7
			lua_pushstring(L, "TOPRIGHT");		// +1     8
			lua_setfield(L, -2, "NAME");		//    -1  7
			lua_pushnumber(L, 1);				// +1     8
			lua_setfield(L, -2, "X");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "Y");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "ANCHORS");		//    -1  7
		lua_settable(L, -3);					//    -2  5
		// BOTTOM LEFT point
		lua_pushnumber(L, 3);					// +1     6
		lua_newtable(L);						// +1     7
			lua_pushstring(L, "BOTTOMLEFT");	// +1     8
			lua_setfield(L, -2, "NAME");		//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "X");			//    -1  7
			lua_pushnumber(L, 1);				// +1     8
			lua_setfield(L, -2, "Y");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "ANCHORS");		//    -1  7
		lua_settable(L, -3);					//    -2  5
		// BOTTOM RIGHT point
		lua_pushnumber(L, 4);					// +1     6
		lua_newtable(L);						// +1     7
			lua_pushstring(L, "BOTTOMRIGHT");	// +1     8
			lua_setfield(L, -2, "NAME");		//    -1  7
			lua_pushnumber(L, 1);				// +1     8
			lua_setfield(L, -2, "X");			//    -1  7
			lua_pushnumber(L, 1);				// +1     8
			lua_setfield(L, -2, "Y");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "ANCHORS");		//    -1  7
		lua_settable(L, -3);					//    -2  5
		// CENTER point
		lua_pushnumber(L, 5);					// +1     6
		lua_newtable(L);						// +1     7
			lua_pushstring(L, "CENTER");		// +1     8
			lua_setfield(L, -2, "NAME");		//    -1  7
			lua_pushnumber(L, 0.5);				// +1     8
			lua_setfield(L, -2, "X");			//    -1  7
			lua_pushnumber(L, 0.5);				// +1     8
			lua_setfield(L, -2, "Y");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "ANCHORS");		//    -1  7
		lua_settable(L, -3);					//    -2  5
	lua_settable(L, reg_table);					//    -2  3

	lua_pop(L, lua_gettop(L)-top);*/
}
