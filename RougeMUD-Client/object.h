#ifndef ROGUEMUD_OBJECT_H
#define ROGUEMUD_OBJECT_H

extern "C"
{
	#include <lua.h>
}
#include <SDL.h>

#include "ns_state_game.h"

using namespace ns_state_game;

/**
	The Object class is the parent of all interface objects.  It is used only in State_Game, and plugs into the state's Lua functionality.
	Some interface objects are hardcoded to prevent modification, such as the world view object (Object_World), or to provide basic functionality, such as
		the texture object (Object_Texture).
	Many interface objects, however, are coded in Lua, allowing free modification of them, such as the chat/command history view object,
		or the F# paging bar object.
**/

class Object
{
	public:
		Object();
		Object(int new_table);
		virtual ~Object();
		virtual void PopulateTable(lua_State *L, int new_table);
		virtual void PopulateRegistry(lua_State *L);
	protected:
	private:
};

int GetObject(int object);

#endif

