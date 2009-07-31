#ifndef ROGUEMUD_OBJECT_GLOBALREGION_H
#define ROGUEMUD_OBJECT_GLOBALREGION_H

#include "ns_game.h"
#include "object_region.h"

using namespace ns_game;

class Object_GlobalRegion : public Object_Region
{
	public:
		Object_GlobalRegion();
		Object_GlobalRegion(int new_table);
		virtual ~Object_GlobalRegion();

		virtual void PopulateTable(lua_State *L, int new_table);
		virtual void PopulateRegistry(lua_State *L);
	protected:
	private:
};

#endif
