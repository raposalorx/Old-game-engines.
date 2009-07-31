#ifndef ROGUEMUD_STATE_LOGIN_H
#define ROGUEMUD_STATE_LOGIN_H

#include "ns_game.h"
#include "state.h"

using namespace ns_game;

/**
**/

class State_Login : public State
{
	public:
		State_Login();
		~State_Login();

		void Event();
		bool Step();
		void Draw();
	protected:
	private:
};

#endif
