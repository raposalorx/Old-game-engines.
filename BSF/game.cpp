#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Init()
{
	// ----------------------------------------
    // Set up SDL
    // ----------------------------------------

	int WIDTH = 800;
	int HEIGHT = 600;

	// Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
		printf("Unable to init SDL: %s\n", SDL_GetError());
		return false;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // Set up the screen
    if (SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL) == NULL)
    {
    	printf("Unable to set video: %s\n", SDL_GetError());
    	return false;
    }

    // ----------------------------------------
    // Set up OpenGL
    // ----------------------------------------

    // Set clear color
    glClearColor(0, 0, 0, 0);

	// Enable 2D texturing
    glEnable(GL_TEXTURE_2D);

	// Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);

    // Initialize modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Check if there were any errors
    if (glGetError() != GL_NO_ERROR)
    {
    	printf("Error in initializing OpenGL\n");
		return false;
    }

    // ----------------------------------------
    // Set up the game's state engine
    // ----------------------------------------

	// Initialize the default state
	game_state = new State_Game();
	state_current = STATE_GAME;

	return true;
}

void Game::Event()
{
	game_state->Event();
}

void Game::Logic()
{
	game_state->Logic();
}

void Game::Render()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	// Let the current state render to the screen
	game_state->Render();

	// Show the newly rendered graphics
	glLoadIdentity();
	SDL_GL_SwapBuffers();
}

bool Game::ChangeState()
{
	// Check if the state should be changed
	Enum_State state_next = game_state->ChangeState();
	if (state_next != STATE_NULL)
	{
		// Delete the current state, and 'switch' to the new one =D
		delete game_state;

		switch (state_next)
		{
		case STATE_NULL:
		case STATE_MENU:
			game_state = new State_Menu();
			break;
		case STATE_GAME:
			game_state = new State_Game();
			break;
		case STATE_EXIT:
			return false;
			break;
		}

		state_current = state_next;
	}

	return true;
}
