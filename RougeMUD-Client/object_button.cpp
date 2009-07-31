#include "object_button.h"

Object_Button::Object_Button()
{
}

Object_Button::Object_Button(int new_table)
{
	PopulateTable(LuaState, new_table);
	PopulateRegistry(LuaState);
}

Object_Button::~Object_Button()
{
}

void Object_Button::PopulateTable(lua_State *L, int new_table)
{
	Object_Secure::PopulateTable(LuaState, new_table);
}

void Object_Button::PopulateRegistry(lua_State *L)
{
	Object_Secure::PopulateRegistry(LuaState);
}
