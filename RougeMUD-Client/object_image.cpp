#include "object_image.h"

Object_Image::Object_Image()
{
}

Object_Image::Object_Image(int new_table)
{
	PopulateTable(LuaState, new_table);
	PopulateRegistry(LuaState);
}

Object_Image::~Object_Image()
{
}

void Object_Image::PopulateTable(lua_State *L, int new_table)
{
	Object_Surface::PopulateTable(LuaState, new_table);
}

void Object_Image::PopulateRegistry(lua_State *L)
{
	Object_Surface::PopulateRegistry(LuaState);
}

void Object_Image::Draw()
{
	
}
