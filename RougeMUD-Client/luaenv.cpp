#include "luaenv.h"

/// Creates and initializes a Lua environment
void init_lua()
{
	// Create the Lua environment
	LuaState = lua_open();
	lua_State *L = LuaState;
	luaL_openlibs(L);

	// Register lua functions
	lua_register(L, "Print", L_Print);
	lua_register(L, "CreateFrame", L_CreateFrame);
	lua_register(L, "GetRegistry", L_DebugRegTable);


	// Create the event registry
	lua_pushstring(L, "EVENT");					// +1     1
	lua_newtable(L);							// +1     2
		// Put event tables into the event registry
		// UI_STEP
		lua_pushstring(L, "UI_STEP");			// +1     3
		lua_newtable(L);						// +1     4
		lua_settable(L, -3);					//    -2  2
		// UI_LOAD
		lua_pushstring(L, "UI_LOAD");			// +1     3
		lua_newtable(L);						// +1     4
		lua_settable(L, -3);					//    -2  2
		// UI_QUIT
		lua_pushstring(L, "UI_QUIT");			// +1     3
		lua_newtable(L);						// +1     4
		lua_settable(L, -3);					//    -2  2
	// Set the event registry table
	lua_settable(L, LUA_REGISTRYINDEX);			//    -2  0

	// Create the object registry
	lua_newtable(L);
	lua_setfield(L, LUA_REGISTRYINDEX, "OBJECT");

	// Create the global region table
	// new_table = {}
	lua_newtable(L);												// +1     1
	int new_table = lua_gettop(L);
	// PopulateTable(new_table)
	Object_GlobalRegion *GlobalRegion = new Object_GlobalRegion(new_table);
	lua_pop(L, lua_gettop(L)-new_table);							//    -?  1
	// new_table[0] = *GlobalRegion
	lua_pushnumber(L, 0);											// +1     2
	lua_pushlightuserdata(L, GlobalRegion);							// +1     3
	lua_settable(L, new_table);										//    -2  1
	// _G.GlobalRegion = new_table
	lua_setglobal(L, "GlobalRegion");								//    -1  0
}

/// Cleans up the C++ objects made by the UI, and destroys the Lua environment
void uninit_lua()
{
	lua_State *L = LuaState;

	// Delete all C++ objects made by the UI
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT"); // +1 (1)
	lua_pushnil(L); // +1 (2)
	while (lua_next(L, -2) != 0) // +2, -1 (3)
	{
		// Get the pointer from 'k', and delete the object it points to
		Object* object = (Object*)lua_touserdata(L, -2);
		delete object;

		// Pop 'v', leave 'k' for next iteration
		lua_pop(L, 1); // -1 (2)
	}

	// Finally, close the Lua environment
    lua_close(L);
}

/// Sends an event call to each listening frame that has a handler set up
void SendEvent(const char* event)
{
	lua_State *L = LuaState;

	// clear the stack
	lua_settop(L, 0);

	// Get the specified event table onto the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "EVENT");	// +1     1
	lua_getfield(L, -1, event);						// +1     2
	int table_event = lua_gettop(L);

	// Get the OBJECT table onto the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     3
	int reg_object = lua_gettop(L);

	// Call the specified event function for each registered object
	lua_pushnil(L);									// +1     4
	while (lua_next(L, table_event) != 0)			// +2 -1  5
	{
		int k = lua_gettop(L)-1;

		// Get the handler onto the stack
		lua_pushvalue(L, -2);						// +1     6
		lua_gettable(L, reg_object);				// +1 -1  6
		lua_getfield(L, -1, "EVENT");				// +1     7
		lua_getfield(L, -1, "HANDLER");				// +1     8
		int func = lua_gettop(L);

		// Push the arguments onto the stack
		lua_pushstring(L, event);					// +1     9

		// Call the handler, if it is set
		if(lua_isfunction(L, func)) lua_call(L, 1, 0); /// TODO: switch to pcall, and maybe organize this chunk better

		// Remove added stack values, keep k for next iteration
		lua_pop(L, lua_gettop(L)-k);				//    -?  4
	}
}

/// Re-calculates the absolute position of the specified region and all those anchored to it
/// Assumes the region(s) the specified region is anchored to already have accurate absolute positioning,
///		if they have any, and [VALID] and [COMPLETED] are true
/// Finding that [COMPLETED] is false is a dead end for resolving positions
void ResolveRegionAbsolutePositions(Object_Region *object)
{
	lua_State *L = LuaState;

	// Get the object's registry table
	// t_object = LUA_REGISTRYINDEX.OBJECT[object]
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");
	lua_pushlightuserdata(L, object);
	lua_gettable(L, -2);
	int t_object = lua_gettop(L);

	//
}

/// TODO: rework this to print to the chat output when they are implemented, instead of the debug window,
///		which the release build does not include, or just use this as a debug function and remove it for the release build
/// Lua function, prints out all values in the stack
int L_Print(lua_State *L)
{
	// Print out all values on the stack
	int top = lua_gettop(L);
	for (int aa = 1; aa <= top; aa++)
	{
		if (lua_isstring(L, aa))
			printf("%s", lua_tostring(L, aa));
		else if (lua_isnil(L, aa))
			printf("%s", "nil");
		else if (lua_isboolean(L, aa))
			printf("%s", lua_toboolean(L, aa) ? "true" : "false");
		else
			printf("%s:%p", luaL_typename(L, aa), lua_topointer(L, aa));
		// End the line
		printf("\n");
	}

	return 0;
}

/// Lua function, creates a new frame, made up of a C++ Object class, and a Lua table
int L_CreateFrame(lua_State *L)
{
	// Create a lua table and give it a link to a new object of the specified type in key [0]

	// Create a new table, and grab its position
	lua_newtable(L);						// +1     1
	int new_table = lua_gettop(L);

	// Fill in the table, by creating the appropriate kind, and then populating its table
	/// TODO: sort the if-else chain by frequency use, in descending order, to optimize creation time, maybe rewrite to use radix tree to search

	if (!strcmp(lua_tostring(L, 1), "frame"))
	{
			// old code, might need to revert to this if light userdata proves insufficient
			//Object_ *object = (Object_*)lua_newuserdata(L, 8);
			//object = new Object_(new_table);
		Object_Frame *object = new Object_Frame(new_table);
		lua_pushlightuserdata(L, object);	// +1     2
	}
	else if (!strcmp(lua_tostring(L, 1), "region"))
	{
		Object_Region *object = new Object_Region(new_table);
		lua_pushlightuserdata(L, object);	// +1     2
	}
	else if (!strcmp(lua_tostring(L, 1), "text"))
	{
		Object_Text *object = new Object_Text(new_table);
		lua_pushlightuserdata(L, object);	// +1     2
	}
	else if (!strcmp(lua_tostring(L, 1), "image"))
	{
		Object_Image *object = new Object_Image(new_table);
		lua_pushlightuserdata(L, object);	// +1     2
	}
	else if (!strcmp(lua_tostring(L, 1), "button"))
	{
		Object_Button *object = new Object_Button(new_table);
		lua_pushlightuserdata(L, object);	// +1     3
	}
	else
	{
		lua_pushstring(L, "Error in function CreateFrame: parameter one has invalid value or type");
		lua_error(L);
		return 0;
	}
	lua_pushnumber(L, 0);					// +1     4
	lua_pushvalue(L, -2);					// +1     5
	lua_settable(L, new_table);				// -2     3

	lua_pushvalue(L, new_table);
	return 1;
}

/// TODO: Remove this function before release!!!  Don't forget to remove the pertinent lua_register() and .h prototype!
int L_DebugRegTable(lua_State *L)
{
	lua_pushvalue(L, LUA_REGISTRYINDEX);	// +1     1
	return 1;
}
