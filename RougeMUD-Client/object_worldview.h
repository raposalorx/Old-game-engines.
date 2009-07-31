#ifndef ROGUEMUD_OBJECT_WORLDVIEW_H
#define ROGUEMUD_OBJECT_WORLDVIEW_H

#include "object_region.h"

class Object_WorldView : public Object_Region
{
	public:
		Object_WorldView();
		Object_WorldView(int new_table);
		virtual ~Object_WorldView();

		virtual void PopulateTable(lua_State *L, int new_table);
		virtual void PopulateRegistry(lua_State *L);
	protected:
	private:
};

#endif
