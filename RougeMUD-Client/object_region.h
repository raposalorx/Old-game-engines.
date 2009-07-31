#ifndef ROGUEMUD_OBJECT_REGION_H
#define ROGUEMUD_OBJECT_REGION_H

#include "object_frame.h"

class Object_Region : public Object_Frame
{
	public:
		Object_Region();
		Object_Region(int new_table);
		virtual ~Object_Region();
		virtual void PopulateTable(lua_State *L, int new_table);
		virtual void PopulateRegistry(lua_State *L);

		int depth, x, y, width, height;
		bool visible;
	protected:
		vector<Object_Region*> parentDB;
		vector<Object_Region*> childDB;
	private:
};

int L_Show(lua_State *L);
int L_Hide(lua_State *L);
int L_GetX(lua_State *L);
int L_SetX(lua_State *L);
int L_GetY(lua_State *L);
int L_SetY(lua_State *L);
int L_GetH(lua_State *L);
int L_SetH(lua_State *L);
int L_GetW(lua_State *L);
int L_SetW(lua_State *L);
/*int L_SetPoint(lua_State *L);
int L_DelPoint(lua_State *L);
int L_GetPoint(lua_State *L);
int L_GetPointCount(lua_State *L);
int L_SetAnchor(lua_State *L);
int L_GetAnchor(lua_State *L);
int L_GetAnchorCount(lua_State *L);
int L_ClearAnchors(lua_State *L);*/

#endif
