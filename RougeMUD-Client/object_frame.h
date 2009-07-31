#ifndef ROGUEMUD_OBJECT_FRAME_H
#define ROGUEMUD_OBJECT_FRAME_H

#include "object.h"

class Object_Frame : public Object
{
	public:
		Object_Frame();
		Object_Frame(int new_table);
		virtual~Object_Frame();
		void PopulateTable(lua_State *L, int new_table);
		virtual void PopulateRegistry(lua_State *L);
	protected:
	private:
};

int L_SetEventHandler(lua_State *L);
int L_NoticeEvent(lua_State *L);
int L_NoticeAllEvents(lua_State *L);
int L_IgnoreEvent(lua_State *L);
int L_IgnoreAllEvents(lua_State *L);

#endif
