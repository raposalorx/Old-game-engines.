#ifndef OBJECT_SIDERBAR_H
#define OBJECT_SIDERBAR_H

#include "object.h"
#include "object_unit.h"
#include "state_game_env.h"
#include "texture.h"

using namespace state_game_env;

class Object_Sidebar : public Object
{
	public:
		Object_Sidebar();
		virtual ~Object_Sidebar();

		virtual void Step();
		virtual void Draw();
	protected:
	private:
		Texture* t_sidebar;
		vector<Object_Unit*> u_selected;
};

Object_Sidebar* CreateObject(Object_Sidebar* new_object, char* name);

#endif
