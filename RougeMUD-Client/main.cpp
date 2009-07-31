#include "game.h"
#include "timer.h"

#include "ns_game.h"

using namespace ns_game;

/**
	The main function simply creates the Game object, and handles the game loop and fps
**/

bool init_net()
{
	// Initialize SDL_net
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		return false;
	}
	// Open a socket on random port
	if (!(sd = SDLNet_UDP_Open(3000)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		return false;
	}
	// Resolve server name
	if (SDLNet_ResolveHost(&srvadd, "127.0.0.1", atoi("2000")) == -1)
	{
		fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", "127.0.0.1", atoi("2000"), SDLNet_GetError());
		return false;
	}
	// Allocate memory for the packet
	if (!(p = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		return false;
	}
	p->address.host = srvadd.host;	// Set the destination host
	p->address.port = srvadd.port;	// And destination port
	return true;
}

bool init_GL()
{
    //Set clear color
    glClearColor( 0, 0, 0, 0 );
	
	glEnable( GL_TEXTURE_2D ); // Need this to display a texture
	
    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, WIDTH, HEIGHT, 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
        return false;
    }

    //If everything initialized
    return true;
}

bool init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    //Create Window
    if( SDL_SetVideoMode( WIDTH, HEIGHT, 32, SDL_OPENGL/* | SDL_FULLSCREEN */) == NULL )
    {
        return false;
    }

    //Initialize OpenGL
    if( init_GL() == false )
    {
        return false;
    }
	
	//Initialize SDL_net
    if( init_net() == false )
    {
        return false;
    }

    //Set caption
    SDL_WM_SetCaption( "RougeMUD", NULL );

    return true;
}

int main (int argc, char** argv)
{
	WIDTH = 640;
	HEIGHT = 480;
	
	if( init() == false )
    {
        return 1;
    }

	// Engine vars
	fps = 30;

	// Initialize the game
	Timer fpsTimer;
	Game game;

	try
	{
		// Call the game loop
		for (;;)
		{
			fpsTimer.Start();

			// Execute a frame's worth of activity
			game.LoopEvents();
			if (game.LoopLogic()) break;
			if (game.ChangeState()) break;
			game.LoopRender();

			// Manage FPS
			if (fpsTimer.GetTime() < 1000/fps)
			{
				SDL_Delay((1000/fps) - fpsTimer.GetTime());
			}
			cur_fps = 1000/fpsTimer.GetTime();
			//printf("CurFPS: %i \n", cur_fps);
		}

		fpsTimer.Stop();
	}
	catch (exception& e)
	{
		printf("%s\n", e.what());
		return 1;
	}
	
	SDL_FreeSurface(screen);

	// Shut down the game
	return 0;
}
