#ifndef ROGUEMUD_OBJECT_IMAGE_H
#define ROGUEMUD_OBJECT_IMAGE_H

#include "object_surface.h"

class Object_Image : public Object_Surface
{
	public:
		Object_Image();
		Object_Image(int new_table);
		virtual ~Object_Image();
		virtual void PopulateTable(lua_State *L, int new_table);
		virtual void PopulateRegistry(lua_State *L);
		virtual void Draw();
	protected:
	private:
};

#endif
