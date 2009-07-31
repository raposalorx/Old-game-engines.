#include "object_frame.h"

Object_Frame::Object_Frame()
{
}

Object_Frame::Object_Frame(int new_table)
{
	PopulateTable(LuaState, new_table);
	PopulateRegistry(LuaState);
}

Object_Frame::~Object_Frame()
{
}

void Object_Frame::PopulateTable(lua_State *L, int new_table)
{
	Object::PopulateTable(LuaState, new_table);

	// _G table
	lua_pushstring(L, "SetEventHandler");			// +1     1
	lua_pushcfunction(L, L_SetEventHandler);		// +1     2
	lua_settable(L, new_table);						//    -2  0
	lua_pushstring(L, "NoticeEvent");				// +1     1
	lua_pushcfunction(L, L_NoticeEvent);			// +1     2
	lua_settable(L, new_table);						//    -2  0
	lua_pushstring(L, "NoticeAllEvents");			// +1     1
	lua_pushcfunction(L, L_NoticeAllEvents);		// +1     2
	lua_settable(L, new_table);						//    -2  0
	lua_pushstring(L, "IgnoreEvent");				// +1     1
	lua_pushcfunction(L, L_IgnoreEvent);			// +1	  2
	lua_settable(L, new_table);						//    -2  0
	lua_pushstring(L, "IgnoreAllEvents");			// +1     1
	lua_pushcfunction(L, L_IgnoreAllEvents);		// +1     2
	lua_settable(L, new_table);						//    -2  0
}

void Object_Frame::PopulateRegistry(lua_State *L)
{
	Object::PopulateRegistry(LuaState);

	// Registry table
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushlightuserdata(L, this);					// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	int reg_table = lua_gettop(L);

	// reg_table.EVENT = {}
	lua_newtable(L);								// +1     3
	lua_setfield(L, reg_table, "EVENT");			//    -2  1
	lua_pop(L, 1);									//    -1  0
}

/// Lua function, sets the object to handle all events through the specified function
/// Parameters are: (handler())
/// handler() is the new function to use to handle events for this object
int L_SetEventHandler(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Get the object's events table on the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushvalue(L, frame);						// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	lua_getfield(L, -1, "EVENT");					// +1     3

	// Push the new handler onto the stack, then put it into the events table
	lua_pushvalue(L, 2);							// +1     4
	lua_setfield(L, -2, "HANDLER");					//    -1  3

	return 0;
}

/// Lua function, registers the object to receive notification by the specified event(s)
int L_NoticeEvent(lua_State *L)
{
	// Get the top of the arguments
	int top = lua_gettop(L);

	// Grab the frame's pointer
	int frame = GetObject(1);

	// Get the events registry table onto the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "EVENT");	// +1     1
	int table_eventreg = lua_gettop(L);

	// Get the object's event table onto the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     2
	lua_pushvalue(L, frame);						// +1     3
	lua_gettable(L, -2);							// +1 -1  3
	lua_getfield(L, -1, "EVENT");					// +1     4
	int table_eventobj = lua_gettop(L);

	// Notice all specified events in stack
	for (int aa = 2; aa <= top; aa++)
	{
		if (lua_isstring(L, aa))
		{
			// Push the appropriate event table onto the stack
			lua_pushvalue(L, aa);					// +1     5
			lua_gettable(L, table_eventreg);		// +1 -1  5
			int table_event = lua_gettop(L);
			/// TODO: make it send an error if the event being registered does not exist, or is HANDLER

			// Set event[frame] to true
			lua_pushvalue(L, frame);				// +1     6
			lua_pushboolean(L, true);				// +1     7
			lua_settable(L, table_event);			//    -2  5

			// Add the event to the object's list
			lua_pushvalue(L, aa);					// +1     6
			lua_pushboolean(L, true);				// +1     7
			lua_settable(L, table_eventobj);		//    -2  5

			lua_pop(L, 1);							// -1     4
		}
		else
		{
			lua_pushstring(L, "Error in function NoticeEvent: parameter has invalid type");
			lua_error(L);
		}
	}

	return 0;
}

/// Lua function, registers the object to receive notification by all events
int L_NoticeAllEvents(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Push the events registry table onto the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "EVENT");	// +1     1
	int table_eventreg = lua_gettop(L);

	// Get the object's events table onto the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     2
	lua_pushvalue(L, frame);						// +1     3
	lua_gettable(L, -2);							// +1 -1  3
	lua_getfield(L, -1, "EVENT");					// +1     4
	int table_eventobj = lua_gettop(L);

	// Notice all events
	lua_pushnil(L);									// +1     5
	while (lua_next(L, table_eventreg) != 0)		// +2 -1  6
	{
		int string_event = lua_gettop(L)-1;
		int table_event = lua_gettop(L);

		// Set event[frame] to true
		lua_pushvalue(L, frame);					// +1     7
		lua_pushboolean(L, true);					// +1     8
		lua_settable(L, table_event);				//    -2  6

		// Add the event to the object's list
		lua_pushvalue(L, string_event);				// +1     7
		lua_pushboolean(L, true);					// +1     8
		lua_settable(L, table_eventobj);			//    -2  6

		// Removes v, k is kept for next iteration
		lua_pop(L, 1);								// -1     5
	}

	return 0;
}

/// Lua function, registers the object to no longer receive notification by the specified event(s)
int L_IgnoreEvent(lua_State *L)
{
	// Get the top of the arguments
	int top = lua_gettop(L);

	// Grab the frame's pointer
	int frame = GetObject(1);

	// Get the events registry table onto the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "EVENT");	// +1     1
	int table_eventreg = lua_gettop(L);

	// Get the object's event table onto the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     2
	lua_pushvalue(L, frame);						// +1     3
	lua_gettable(L, -2);							// +1 -1  3
	lua_getfield(L, -1, "EVENT");					// +1     4
	int table_eventobj = lua_gettop(L);

	// Ignore all specified events in stack
	for (int aa = 2; aa <= top; aa++)
	{
		if (lua_isstring(L, aa))
		{
			// Push the appropriate event table onto the stack
			lua_pushvalue(L, aa);					// +1     5
			lua_gettable(L, table_eventreg);		// +1 -1  5
			int table_event = lua_gettop(L);
			/// TODO: make it send an error if the event being unregistered does not exist, or is HANDLER

			// Set table[frame] to nil
			lua_pushvalue(L, frame);				// +1     6
			lua_pushnil(L);							// +1     7
			lua_settable(L, table_event);			//    -2  5

			// Remove the event from the object's list
			lua_pushvalue(L, aa);					// +1     6
			lua_pushnil(L);							// +1     7
			lua_settable(L, table_eventobj);		//    -2  5

			lua_pop(L, 1);							//    -1  4
		}
		else
		{
			lua_pushstring(L, "Error in function Event: parameter has invalid type");
			lua_error(L);
		}
	}

	return 0;
}

/// Lua function, registers the object to no longer receive notification by all events
int L_IgnoreAllEvents(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Push the events registry table onto the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "EVENT");	// +1     1
	int table_eventreg = lua_gettop(L);

	// Get the object's events table onto the stack
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     2
	lua_pushvalue(L, frame);						// +1     3
	lua_gettable(L, -2);							// +1 -1  3
	lua_getfield(L, -1, "EVENT");					// +1     4
	int table_eventobj = lua_gettop(L);

	// Ignore all events
	lua_pushnil(L);									// +1     5
	while (lua_next(L, table_eventreg) != 0)		// +2 -1  6
	{
		int string_event = lua_gettop(L)-1;
		int table_event = lua_gettop(L);

		// Set event[frame] to nil
		lua_pushvalue(L, frame);					// +1     7
		lua_pushnil(L);								// +1     8
		lua_settable(L, table_event);				//    -2  6

		// Remove the event from the object's list
		lua_pushvalue(L, string_event);				// +1     7
		lua_pushnil(L);								// +1     8
		lua_settable(L, table_eventobj);			//    -2  6

		// Removes v, k is kept for next iteration
		lua_pop(L, 1);								//    -1  5
	}

	return 0;
}
