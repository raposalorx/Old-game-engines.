#ifndef ROGUEMUD_OBJECT_BUTTON_H
#define ROGUEMUD_OBJECT_BUTTON_H

#include "object_secure.h"

class Object_Button : public Object_Secure
{
	public:
		Object_Button();
		Object_Button(int new_table);
		virtual ~Object_Button();
		virtual void PopulateTable(lua_State *L, int new_table);
		virtual void PopulateRegistry(lua_State *L);
	protected:
	private:
};

#endif
