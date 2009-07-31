#ifndef ROGUEMUD_OBJECT_SECURE_H
#define ROGUEMUD_OBJECT_SECURE_H

#include "object_region.h"

class Object_Secure : public Object_Region
{
	public:
		Object_Secure();
		Object_Secure(int new_table);
		virtual ~Object_Secure();
		virtual void PopulateTable(lua_State *L, int new_table);
		virtual void PopulateRegistry(lua_State *L);
	protected:
	private:
};

#endif
