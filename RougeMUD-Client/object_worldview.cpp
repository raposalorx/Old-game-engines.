#include "object_worldview.h"

Object_WorldView::Object_WorldView()
{
}

Object_WorldView::Object_WorldView(int new_table)
{
	PopulateTable(LuaState, new_table);
	PopulateRegistry(LuaState);
}

Object_WorldView::~Object_WorldView()
{
}

void Object_WorldView::PopulateTable(lua_State *L, int new_table)
{
	Object_Region::PopulateTable(L, new_table);
}

void Object_WorldView::PopulateRegistry(lua_State *L)
{
	Object_Region::PopulateRegistry(L);
}
