#ifndef ROGUEMUD_OBJECT_SURFACE_H
#define ROGUEMUD_OBJECT_SURFACE_H

#include "object_region.h"
#include "ns_game.h"

using namespace ns_game;

class Object_Surface : public Object_Region
{
	public:
		Object_Surface();
		Object_Surface(int new_table);
		virtual ~Object_Surface();
		virtual void PopulateTable(lua_State *L, int new_table);
		virtual void PopulateRegistry(lua_State *L);
		virtual void Draw();
	protected:
	private:
};

#endif
