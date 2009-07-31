#ifndef ROGUEMUD_OBJECT_TEXT_H
#define ROGUEMUD_OBJECT_TEXT_H

#include "object_surface.h"

class Object_Text : public Object_Surface
{
	public:
		Object_Text();
		Object_Text(int new_table);
		virtual ~Object_Text();
		virtual void PopulateTable(lua_State *L, int new_table);
		virtual void PopulateRegistry(lua_State *L);
		virtual void Draw();
	protected:
	private:
};

#endif
