#ifndef OBJECT_UNIT_SHIP_H
#define OBJECT_UNIT_SHIP_H

#include <math.h>

#include "object_unit.h"
#include "state_game_env.h"
#include "texture.h"

using namespace state_game_env;

struct Ship_Section
{
	Texture *sprite;
	double x, y;
};

struct Ship_Weapon
{
	Texture *sprite_turret;
	double x, y;
};

class Object_Ship : public Object_Unit
{
	public:
		Object_Ship();
		virtual ~Object_Ship();

		virtual void Step();
		virtual void Draw();
	protected:
	private:
		Texture *t_core;
		vector<Ship_Section> sectionDB;
		vector<Ship_Weapon> weaponDB;
};

Object_Ship *CreateObject(Object_Ship *new_object, const char *name);

#endif
