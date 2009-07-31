#ifndef STATE_MENU_H
#define STATE_MENU_H

#include <vector>

#include "state.h"
#include "texture.h"

using namespace std;

class State_Menu : public State
{
	public:
		State_Menu();
		~State_Menu();

		void Event();
		void Logic();
		void Render();
		Enum_State ChangeState();
	protected:
	private:
};

#endif
