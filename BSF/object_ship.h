#ifndef OBJECT_UNIT_SHIP_H
#define OBJECT_UNIT_SHIP_H

#include <math.h>

#include "object_unit.h"
#include "state_game_env.h"
#include "texture.h"

using namespace state_game_env;

class Object_Ship : public Object_Unit
{
	public:
		Object_Ship();
		virtual ~Object_Ship();

		virtual void Step();
		virtual void Draw();
	protected:
	private:
		Texture* t_core;
};

Object_Ship* CreateObject(Object_Ship* new_object, char* name);

#endif
