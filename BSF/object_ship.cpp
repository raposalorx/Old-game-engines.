#include "object_ship.h"

Object_Ship::Object_Ship()
{
	rot = -10;
	vel_mag = 1;
	vel_dir = -10;

	if (tree_textures.Search("spr_hestia"))
		t_core = (Texture*)tree_textures.GetLast();
	else
		t_core = NULL;
		
	w = t_core->GetW();
	h = t_core->GetH();
}

Object_Ship::~Object_Ship()
{
}

void Object_Ship::Step()
{
	x += vel_mag * cos(vel_dir / 180 * 3.14159265);
	y -= vel_mag * sin(vel_dir / 180 * 3.14159265);
}

void Object_Ship::Draw()
{
	if (t_core != NULL)
		t_core->Draw(x-screen_x, y-screen_y, -rot);
}

// Factory function
Object_Ship* CreateObject(Object_Ship* new_object, const char* name)
{
	objectDB.push_back(new_object);
	unitDB.push_back(new_object);
	if (name != NULL)
		tree_objects.AddString(name, new_object, 0);
	return new_object;
}
