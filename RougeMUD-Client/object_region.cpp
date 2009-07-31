#include "object_region.h"

Object_Region::Object_Region()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	depth = 0;
	visible = true;
}

Object_Region::Object_Region(int new_table)
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	depth = 0;
	visible = true;
	PopulateTable(LuaState, new_table);
	PopulateRegistry(LuaState);
}

Object_Region::~Object_Region()
{
}

void Object_Region::PopulateTable(lua_State *L, int new_table)
{
	Object_Frame::PopulateTable(LuaState, new_table);

	// _G table
	lua_pushstring(L, "Show");				// +1     1
	lua_pushcfunction(L, L_Show);			// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "Hide");				// +1     1
	lua_pushcfunction(L, L_Hide);			// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "GetX");				// +1     1
	lua_pushcfunction(L, L_GetX);			// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "GetY");				// +1     1
	lua_pushcfunction(L, L_GetY);			// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "GetW");				// +1     1
	lua_pushcfunction(L, L_GetW);			// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "GetH");				// +1     1
	lua_pushcfunction(L, L_GetH);			// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "SetX");				// +1     1
	lua_pushcfunction(L, L_SetX);			// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "SetY");				// +1     1
	lua_pushcfunction(L, L_SetY);			// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "SetW");				// +1     1
	lua_pushcfunction(L, L_SetW);			// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "SetH");				// +1     1
	lua_pushcfunction(L, L_SetH);			// +1     2
	lua_settable(L, new_table);				//    -2  0
/*	lua_pushstring(L, "SetPoint");			// +1     1
	lua_pushcfunction(L, L_SetPoint);		// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "DelPoint");			// +1     1
	lua_pushcfunction(L, L_DelPoint);		// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "GetPoint");			// +1     1
	lua_pushcfunction(L, L_GetPoint);		// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "GetPointCount");		// +1     1
	lua_pushcfunction(L, L_GetPointCount);	// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "SetAnchor");			// +1     1
	lua_pushcfunction(L, L_SetAnchor);		// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "SetAnchor");			// +1     1
	lua_pushcfunction(L, L_SetAnchor);		// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "GetAnchor");			// +1     1
	lua_pushcfunction(L, L_GetAnchor);		// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "GetAnchorCount");	// +1     1
	lua_pushcfunction(L, L_GetAnchorCount);	// +1     2
	lua_settable(L, new_table);				//    -2  0
	lua_pushstring(L, "ClearAnchors");		// +1     1
	lua_pushcfunction(L, L_ClearAnchors);	// +1     2
	lua_settable(L, new_table);				//    -2  0*/
}

void Object_Region::PopulateRegistry(lua_State *L)
{
	Object_Frame::PopulateRegistry(LuaState);

	int top = lua_gettop(L);

/*	// Registry table
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushlightuserdata(L, this);					// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	int reg_table = lua_gettop(L);
	// Point table
	lua_pushstring(L, "POINT");					// +1     4
	lua_newtable(L);							// +1     5
		// Point count field
		lua_pushnumber(L, 0);					// +1     6
		lua_pushnumber(L, 5);					// +1     7
		lua_settable(L, -3);					//    -2  5
		// TOP LEFT point
		lua_pushnumber(L, 1);					// +1     6
		lua_newtable(L);						// +1     7
			lua_pushstring(L, "TOPLEFT");		// +1     8
			lua_setfield(L, -2, "NAME");		//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "X");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "Y");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "ANCHORS");		//    -1  7
		lua_settable(L, -3);					//    -2  5
		// TOP RIGHT point
		lua_pushnumber(L, 2);					// +1     6
		lua_newtable(L);						// +1     7
			lua_pushstring(L, "TOPRIGHT");		// +1     8
			lua_setfield(L, -2, "NAME");		//    -1  7
			lua_pushnumber(L, 1);				// +1     8
			lua_setfield(L, -2, "X");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "Y");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "ANCHORS");		//    -1  7
		lua_settable(L, -3);					//    -2  5
		// BOTTOM LEFT point
		lua_pushnumber(L, 3);					// +1     6
		lua_newtable(L);						// +1     7
			lua_pushstring(L, "BOTTOMLEFT");	// +1     8
			lua_setfield(L, -2, "NAME");		//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "X");			//    -1  7
			lua_pushnumber(L, 1);				// +1     8
			lua_setfield(L, -2, "Y");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "ANCHORS");		//    -1  7
		lua_settable(L, -3);					//    -2  5
		// BOTTOM RIGHT point
		lua_pushnumber(L, 4);					// +1     6
		lua_newtable(L);						// +1     7
			lua_pushstring(L, "BOTTOMRIGHT");	// +1     8
			lua_setfield(L, -2, "NAME");		//    -1  7
			lua_pushnumber(L, 1);				// +1     8
			lua_setfield(L, -2, "X");			//    -1  7
			lua_pushnumber(L, 1);				// +1     8
			lua_setfield(L, -2, "Y");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "ANCHORS");		//    -1  7
		lua_settable(L, -3);					//    -2  5
		// CENTER point
		lua_pushnumber(L, 5);					// +1     6
		lua_newtable(L);						// +1     7
			lua_pushstring(L, "CENTER");		// +1     8
			lua_setfield(L, -2, "NAME");		//    -1  7
			lua_pushnumber(L, 0.5);				// +1     8
			lua_setfield(L, -2, "X");			//    -1  7
			lua_pushnumber(L, 0.5);				// +1     8
			lua_setfield(L, -2, "Y");			//    -1  7
			lua_pushnumber(L, 0);				// +1     8
			lua_setfield(L, -2, "ANCHORS");		//    -1  7
		lua_settable(L, -3);					//    -2  5
	lua_settable(L, reg_table);					//    -2  3

	// Anchor table
	// t_new = {}
	lua_pushstring(L, "ANCHOR");				// +1     4
	lua_newtable(L);							// +1     5
	int t_new = lua_gettop(L);
		// Anchor count field
		lua_pushnumber(L, 0);					// +1     6
		lua_pushnumber(L, 0);					// +1     7
		lua_settable(L, t_new);					//    -2  5
		// t_new.COMPLETED = false
		lua_pushboolean(L, false);				// +1     6
		lua_setfield(L, t_new, "COMPLETED");	//    -1  5
		// t_new.VALID = false
		lua_pushboolean(L, false);				// +1     6
		lua_setfield(L, t_new, "VALID");		//    -1  5
	// reg_table.ANCHOR = t_new
	lua_settable(L, reg_table);					//    -2  3*/

	lua_pop(L, lua_gettop(L)-top);
}

/// Lua function, sets the region's render status to true
int L_Show(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Make the region visible
	((Object_Region*)lua_touserdata(L, frame))->visible = true;
	return 0;
}

/// Lua function, sets the region's render status to false
int L_Hide(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Make the region invisible
	((Object_Region*)lua_touserdata(L, frame))->visible = false;
	return 0;
}

int L_GetX(lua_State *L)
{
	int frame = GetObject(1);

	Object_Region *object = (Object_Region*)lua_topointer(L, frame);

	lua_pushnumber(L, object->x);

	return 1;
}

int L_SetX(lua_State *L)
{
	int frame = GetObject(1);

	Object_Region *object = (Object_Region*)lua_topointer(L, frame);

	object->x = lua_tonumber(L, 2);

	return 0;
}

int L_GetY(lua_State *L)
{
	int frame = GetObject(1);

	Object_Region *object = (Object_Region*)lua_topointer(L, frame);

	lua_pushnumber(L, object->y);

	return 1;
}

int L_SetY(lua_State *L)
{
	int frame = GetObject(1);

	Object_Region *object = (Object_Region*)lua_topointer(L, frame);

	object->y = lua_tonumber(L, 2);

	return 0;
}

int L_GetH(lua_State *L)
{
	int frame = GetObject(1);

	Object_Region *object = (Object_Region*)lua_topointer(L, frame);

	lua_pushnumber(L, object->height);

	return 1;
}

int L_SetH(lua_State *L)
{
	int frame = GetObject(1);

	Object_Region *object = (Object_Region*)lua_topointer(L, frame);

	object->height = lua_tonumber(L, 2);

	return 0;
}

int L_GetW(lua_State *L)
{
	int frame = GetObject(1);

	Object_Region *object = (Object_Region*)lua_topointer(L, frame);

	lua_pushnumber(L, object->width);

	return 1;
}

int L_SetW(lua_State *L)
{
	int frame = GetObject(1);

	Object_Region *object = (Object_Region*)lua_topointer(L, frame);

	object->width = lua_tonumber(L, 2);

	return 0;
}


/*/// Lua function, sets the values of the specified custom point, making a new one if necessary
/// Parameters are: ("point", #x, #y)
/// "point" is the name of the point, #x/#y, when multiplied by width/height, are the x/y offsets from the top left corner of the region
int L_SetPoint(lua_State *L)
{
	/// TODO: add checks to prevent overwriting of preset points
	/// TODO: make it add a second link with a numerical index to the added table

	// Grab the frame's pointer
	int frame = GetObject(1);

	// Get the object's point table on the stack
	// local t_point = LUA_REGISTRYINDEX.OBJECT[frame].POINT
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushvalue(L, frame);						// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	lua_getfield(L, -1, "POINT");					// +1     3
	int t_point = lua_gettop(L);

	// Add a new point, with the specified name
	// local t_newpoint = {}
	lua_pushvalue(L, 2);							// +1     4
	lua_newtable(L);								// +1     5
	int t_newpoint = lua_gettop(L);
		// t_newpoint.NAME = name
		lua_pushvalue(L, 2);						// +1     6
		lua_setfield(L, t_newpoint, "NAME");		//    -1  5
		// t_newpoint.X = new_x
		lua_pushvalue(L, 3);						// +1     6
		lua_setfield(L, t_newpoint, "X");			//    -1  5
		// t_newpoint.Y = new_y
		lua_pushvalue(L, 4);						// +1     6
		lua_setfield(L, t_newpoint, "Y");			//    -1  5
	// t_point[name] = t_newpoint
	lua_settable(L, t_point);						//    -2  3

	// Increment the value of [0] by one
	// local num = t_newpoint[0]
	lua_pushnumber(L, 0);							// +1     4
	lua_gettable(L, t_newpoint);					// +1 -1  4
	lua_Number num = lua_tonumber(L, -1);
	// t_newpoint[0] = num+1
	lua_pushnumber(L, 0);							// +1     5
	lua_pushnumber(L, num+1);						// +1     6
	lua_settable(L, t_newpoint);					//    -2  4

	return 0;
}

/// Lua function, deletes the specified point on the region
/// Parameters are: ("point")
/// "point" is the name of the point to delete
int L_DelPoint(lua_State *L)
{
	/// TODO: make it shift the larger indexes back down to fill the gap left
	/// TODO: make it also able to delete points by numerical index
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Get the object's point table on the stack
	// local t_point = LUA_REGISTRYINDEX.OBJECT[frame].POINT
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushvalue(L, frame);						// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	lua_getfield(L, -1, "POINT");					// +1     3
	int t_point = lua_gettop(L);

	// Check if the point exists
	// if (type(t_point[name]) == 'table') then
	lua_pushvalue(L, 2);							// +1     4
	lua_gettable(L, t_point);						// +1 -1  4
	if (lua_istable(L, -1))
	{
		// Delete the point
		// t_point[name] = nil
		lua_pushvalue(L, 2);						// +1     5
		lua_pushnil(L);								// +1     6
		lua_settable(L, t_point);					//    -2  4

		// Decrement the value of [0] by one
		// num = t_point[0]
		lua_pushnumber(L, 0);						// +1     5
		lua_gettable(L, t_point);					// +1 -1  5
		lua_Number num = lua_tonumber(L, -1);
		// t_point[0] = num+1
		lua_pushnumber(L, 0);						// +1     6
		lua_pushnumber(L, num-1);					// +1     7
		lua_settable(L, t_point);					//    -2  5
	}

	return 0;
}

/// Lua function, returns the information on the specified point, by number or by
int L_GetPoint(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Get the object's point table
	// local t_point = LUA_REGISTRYINDEX.OBJECT[frame].POINT
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushvalue(L, frame);						// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	lua_getfield(L, -1, "POINT");					// +1     3
	int t_point = lua_gettop(L);

	// Get the table of the specified point
	/// TODO: add checks to see that the specified point exists, and is not index [0]

	// Get the values from the point onto the stack and return them
	// return t_point.NAME, t_point.X, t_point.Y, t_point.ANCHORS
	lua_getfield(L, t_point, "NAME");				// +1     4
	lua_getfield(L, t_point, "X");					// +1     5
	lua_getfield(L, t_point, "Y");					// +1     6
	lua_getfield(L, t_point, "ANCHORS");			// +1     7

	return 4;
}

/// Lua function, returns the number of points on the region
int L_GetPointCount(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Get the object's point table
	// local t_point = LUA_REGISTRYINDEX.OBJECT[frame].POINT
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushvalue(L, frame);						// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	lua_getfield(L, -1, "POINT");					// +1     3
	int t_point = lua_gettop(L);

	// Get the value of [0] on the stack
	// return t_point[0]
	lua_pushnumber(L, 0);							// +1     4
	lua_gettable(L, t_point);							// +1 -1  4

	return 1;
}

/// Lua function, edits the X and Y values of the specified point
int L_EditPoint(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Get the object's point table
	// local t_point = LUA_REGISTRYINDEX.OBJECT[frame].POINT
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushvalue(L, frame);						// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	lua_getfield(L, -1, "POINT");					// +1     3
	int t_point = lua_gettop(L);

	// Get the table of the specified point
	/// TODO: add checks to make sure the specified point exists, and is not index [0]
	// t_point = t_point[point]
	lua_pushvalue(L, 2);							// +1     4
	lua_gettable(L, t_point);						// +1 -1  4
	t_point = lua_gettop(L);

	// Add in the new x and y values
	// t_point.X = new_x
	lua_pushvalue(L, 3);							// +1     5
	lua_setfield(L, t_point, "X");					//    -1  4
	// t_point.Y = new_y
	lua_pushvalue(L, 4);							// +1     5
	lua_setfield(L, t_point, "Y");					//    -1  4

	return 0;
}


/// Lua function, sets the specified anchor point to the specified coordinates
/// Parameters are: ("source", destobject, "dest", #off_1, #off_2)
/// "source" is the point to anchor, "dest" is the point "source" will be anchored to,
/// "destobject" is the object that point "dest" belongs to
/// #off_1 is the first offset, #off_2 is the second offset, both or just one can be non-nil
int L_SetAnchor(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Grab the destination object's pointer
	int dest = GetObject(3);

	// Get the object's anchor table
	// local t_anchor = LUA_REGISTRYINDEX.OBJECT[frame].ANCHOR
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushvalue(L, frame);						// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	lua_getfield(L, -1, "ANCHOR");					// +1     3
	int t_anchor = lua_gettop(L);

	// Check if the anchor list is already full
	// if t_anchor.COMPLETED == true then return end
	lua_getfield(L, t_anchor, "COMPLETED");			// +1     4
	if (lua_toboolean(L, -1) == 1)
		return 0;
	lua_pop(L, 1);									//    -1  3

	// Check if the anchor is self-referential
	// if dest == frame then self_ref = true else self_ref = false end
	bool self_ref;
	if (lua_equal(L, frame, dest))
		self_ref = true;
	else
		self_ref = false;

	// Find which axes will be set
	int x, y;
	// if x_off == nil then
	if (lua_isnil(L, 5))
		x = 0;
	else
		x = 1;
	// if y_off == nil then
	if (lua_isnil(L, 6))
		y = 0;
	else
		y = 1;
	// Send an error if neither offset is defined
	if (x == 0 and y == 0)
	{
		/// TODO: add an error here
		return 0;
	}

	// Check if the right slots are available
	// Move to the second slot if the anchor is self-referential
	if (self_ref)
	{
		x *= 2;
		y *= 2;
	}
	// Get the anchor slots
	// t_x1 = t_anchor.X1
	lua_getfield(L, t_anchor, "X1");			// +1     4
	int t_x1 = lua_gettop(L);
	// t_y1 = t_anchor.Y1
	lua_getfield(L, t_anchor, "Y1");			// +1     5
	int t_y1 = lua_gettop(L);
	// t_x2 = t_anchor.X2
	lua_getfield(L, t_anchor, "X2");			// +1     6
	int t_x2 = lua_gettop(L);
	// t_y2 = t_anchor.Y2
	lua_getfield(L, t_anchor, "Y2");			// +1     7
	int t_y2 = lua_gettop(L);
	// Check if the desired slot is the first one
	if (x == 1 or y == 1)
	{
		// If the first slot is taken, move to the second slot
		// if x == 1 and t_x1 != nil then x = x*2 y = y*2
		if (x == 1 && lua_isnil(L, t_x1) == 0)
		{
			x *= 2;
			y *= 2;
		}
		// elseif y == 1 and t_y1 != nil then x = x*2 y = y*2 end
		else if (y == 1 && lua_isnil(L, t_y1) == 0)
		{
			x *= 2;
			y *= 2;
		}
	}
	// Check if the desired slot is the second one
	if (x == 2 or y == 2)
	{
		// If the second slot is taken, silently fail
		// if x == 2 and t_x2 != nil then return
		if (x == 2 && lua_isnil(L, t_x2) == 0)
			return 0;
		// elseif y == 2 and t_y2 != nil then return end
		else if (y == 2 && lua_isnil(L, t_y2) == 0)
			return 0;
	}
	// Set the coord anchor's values
	// Make the new coord anchor
	// local t_new = {}
	lua_newtable(L);
	int t_new = lua_gettop(L);
	if (x == 1)
	{
		// t_new.SOURCE = source
		lua_pushvalue(L, 2);
		lua_setfield(L, t_new, "SOURCE");
		// t_new.OFFSET = off_1
		lua_pushvalue(L, 5);
		lua_setfield(L, t_new, "OFFSET");
		// t_new.DEST_OBJECT = destobject
		lua_pushvalue(L, dest);
		lua_setfield(L, t_new, "DEST_OBJECT");
		// t_new.DEST_POINT = dest
		lua_pushvalue(L, 4);
		lua_setfield(L, t_new, "DEST_POINT");
		// t_anchor.X1 = t_new
		lua_setfield(L, t_anchor, "X1");
	}
	else if (x == 2)
	{
		// t_new.SOURCE = source
		lua_pushvalue(L, 2);
		lua_setfield(L, t_new, "SOURCE");
		// t_new.OFFSET = off_1
		lua_pushvalue(L, 5);
		lua_setfield(L, t_new, "OFFSET");
		// t_new.DEST_OBJECT = destobject
		lua_pushvalue(L, dest);
		lua_setfield(L, t_new, "DEST_OBJECT");
		// t_new.DEST_POINT = dest
		lua_pushvalue(L, 4);
		lua_setfield(L, t_new, "DEST_POINT");
		// t_anchor.X2 = t_new
		lua_setfield(L, t_anchor, "X2");
	}
	// Make the new coord anchor
	// local t_new = {}
	lua_newtable(L);
	t_new = lua_gettop(L);
	if (y == 1)
	{
		// t_new.SOURCE = source
		lua_pushvalue(L, 2);
		lua_setfield(L, t_new, "SOURCE");
		// if x == 0 then t_new.OFFSET = off_1 else t_new.OFFSET = off_2
		if (x == 0)
			lua_pushvalue(L, 5);
		else
			lua_pushvalue(L, 6);
		lua_setfield(L, t_new, "OFFSET");
		// t_new.DEST_OBJECT = destobject
		lua_pushvalue(L, dest);
		lua_setfield(L, t_new, "DEST_OBJECT");
		// t_new.DEST_POINT = dest
		lua_pushvalue(L, 4);
		lua_setfield(L, t_new, "DEST_POINT");
		// t_anchor.Y1 = t_new
		lua_setfield(L, t_anchor, "Y1");
	}
	else if (y == 2)
	{
		// t_new.SOURCE = source
		lua_pushvalue(L, 2);
		lua_setfield(L, t_new, "SOURCE");
		// if x == 0 then t_new.OFFSET = off_1 else t_new.OFFSET = off_2
		if (x == 0)
			lua_pushvalue(L, 5);
		else
			lua_pushvalue(L, 6);
		lua_setfield(L, t_new, "OFFSET");
		// t_new.DEST_OBJECT = destobject
		lua_pushvalue(L, dest);
		lua_setfield(L, t_new, "DEST_OBJECT");
		// t_new.DEST_POINT = dest
		lua_pushvalue(L, 4);
		lua_setfield(L, t_new, "DEST_POINT");
		// t_anchor.Y2 = t_new
		lua_setfield(L, t_anchor, "Y2");
	}

	/// TODO: make it add the raw anchors, and make it check to prevent the same axis from being anchored multiple times
	/// TODO: make it check and set [COMPLETED] if the anchors are now complete

	return 0;
}

/// Lua function, returns the information on the specified anchor
int L_GetAnchor(lua_State *L)
{
	/// TODO
	return 6;
}

/// Lua function, returns the number of anchors that the region has set
int L_GetAnchorCount(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Get the object's anchor table
	// local t_anchor = LUA_REGISTRYINDEX.OBJECT[frame].ANCHOR
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushvalue(L, frame);						// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	lua_getfield(L, -1, "ANCHOR");					// +1     3
	int t_anchor = lua_gettop(L);

	// Count how many raw anchors are set
	lua_pushnil(L);									// +1     4
	int anchors;
	for (anchors = 0; anchors < 4; anchors++)
	{
		// if t_anchor[anchors] == nil then break end
		lua_pop(L, 1);								//    -1  3
		lua_pushnumber(L, anchors);					// +1     4
		lua_gettable(L, t_anchor);					// +1 -1  4
		if (lua_isnil(L, -1) == 0)
			break;
	}

	// return anchors
	lua_pushnumber(L, anchors);
	return 1;
}

/// Lua function, clears all of the region's anchors
int L_ClearAnchors(lua_State *L)
{
	// Grab the frame's pointer
	int frame = GetObject(1);

	// Get the object's anchor table
	// local t_anchor = LUA_REGISTRYINDEX.OBJECT[frame].ANCHOR
	lua_getfield(L, LUA_REGISTRYINDEX, "OBJECT");	// +1     1
	lua_pushvalue(L, frame);						// +1     2
	lua_gettable(L, -2);							// +1 -1  2
	lua_getfield(L, -1, "ANCHOR");					// +1     3
	int t_anchor = lua_gettop(L);

	// Clear the anchors
	// t_anchor.X1 = nil
	lua_pushnil(L);									// +1     4
	lua_setfield(L, t_anchor, "X1");				//    -1  3
	// t_anchor.X2 = nil
	lua_pushnil(L);									// +1     4
	lua_setfield(L, t_anchor, "X2");				//    -1  3
	// t_anchor.Y1 = nil
	lua_pushnil(L);									// +1     4
	lua_setfield(L, t_anchor, "Y1");				//    -1  3
	// t_anchor.Y2 = nil
	lua_pushnil(L);									// +1     4
	lua_setfield(L, t_anchor, "Y2");				//    -1  3
	// t_anchor[1] = nil
	lua_pushnumber(L, 1);							// +1     4
	lua_pushnil(L);									// +1     5
	lua_settable(L, t_anchor);						//    -2  3
	// t_anchor[2] = nil
	lua_pushnumber(L, 2);							// +1     4
	lua_pushnil(L);									// +1     5
	lua_settable(L, t_anchor);						//    -2  3
	// t_anchor[3] = nil
	lua_pushnumber(L, 3);							// +1     4
	lua_pushnil(L);									// +1     5
	lua_settable(L, t_anchor);						//    -2  3
	// t_anchor[4] = nil
	lua_pushnumber(L, 4);							// +1     4
	lua_pushnil(L);									// +1     5
	lua_settable(L, t_anchor);						//    -2  3

	// Set COMPLETE and VALID to false
	// t_anchor.COMPLETED = false
	lua_pushboolean(L, false);						// +1     4
	lua_setfield(L, t_anchor, "COMPLETED");			//    -1  3
	// t_anchor.VALID = false
	lua_pushboolean(L, false);						// +1     4
	lua_setfield(L, t_anchor, "VALID");				//    -1  3

	return 0;
}*/
