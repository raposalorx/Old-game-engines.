#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "object.h"
#include "object_sidebar.h"
#include "object_ship.h"
#include "object_unit.h"
#include "state.h"
#include "state_env.h"
#include "state_game_env.h"
#include "texture.h"

using namespace state_env;
using namespace state_game_env;

class State_Game : public State
{
	public:
		State_Game();
		~State_Game();

		void Event();
		void Logic();
		void Render();
		Enum_State ChangeState();
	protected:
	private:
		//int view_x, view_y, view_w, view_h, view_x_max, view_y_max, mini_view_w, mini_view_h;
};

#endif
