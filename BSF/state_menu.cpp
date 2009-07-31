#include "state_menu.h"

State_Menu::State_Menu()
{
}

State_Menu::~State_Menu()
{
}

void State_Menu::Event()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// Exit if the window is closed
		case SDL_QUIT:
			state_next = STATE_EXIT;
			break;

			// Check for keypresses
		case SDL_KEYDOWN:
			{
			}
		}
	}
}

void State_Menu::Logic()
{
}

void State_Menu::Render()
{
}

Enum_State State_Menu::ChangeState()
{
	return state_next;
}
