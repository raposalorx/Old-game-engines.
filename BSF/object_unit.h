#ifndef OBJECT_UNIT_H
#define OBJECT_UNIT_H

#include "object.h"
#include "state_game_env.h"
#include "texture.h"

using namespace state_game_env;

class Object_Unit : public Object
{
	public:
		Object_Unit();
		virtual ~Object_Unit();

		virtual void Step();
		virtual void Draw();

		void Move(int new_x, int new_y);
		void SetTeam(int new_team);
		int GetTeam();
		virtual double GetX();
		virtual double GetY();
		virtual int GetW();
		virtual int GetH();
	protected:
		int team;
		double x, y, w, h, rot, vel_mag, vel_dir;
	private:
};

Object_Unit* CreateObject(Object_Unit* new_object, const char* name);

#endif
