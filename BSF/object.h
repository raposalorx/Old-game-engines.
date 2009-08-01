#ifndef OBJECT_H
#define OBJECT_H

#include "state_game_env.h"

using namespace state_game_env;

class Object
{
	public:
		Object() {};
		virtual ~Object() {};

		virtual void Step() {};
		virtual void Draw() {};
		
		virtual double GetX() {};
		virtual double GetY() {};
		virtual int GetW() {};
		virtual int GetH() {};
	protected:
	private:
};

#endif
