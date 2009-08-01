#include "object_unit.h"

Object_Unit::Object_Unit()
{
	team = 0;
	x = 0;
	y = 0;
	rot = 0;
	vel_mag = 0;
	vel_dir = 0;
}

Object_Unit::~Object_Unit()
{
}

void Object_Unit::Step()
{
}

void Object_Unit::Draw()
{
}

void Object_Unit::Move(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
}

void Object_Unit::SetTeam(int new_team)
{
	team = new_team;
}

int Object_Unit::GetTeam()
{
	return team;
}

double Object_Unit::GetX()
{
	return x;
}

double Object_Unit::GetY()
{
	return y;
}

// Factory function
Object_Unit* CreateObject(Object_Unit* new_object, const char* name)
{
	objectDB.push_back(new_object);
	unitDB.push_back(new_object);
	if (name != NULL)
		tree_objects.AddString(name, new_object, 0);
	return new_object;
}
