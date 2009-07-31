#include "game.h"
#include "timer.h"

/**
	Server notes:
	-handles ALL player actions that affect server-side data, making sure they are legal actions to prevent hacking
	-keeps a record of significant events, as well as constantly keeping player/server data updated and backed up
	-maybe route chat through an irc protocol?
		-would make things easier, for us and the server
		-for security, go all-out on channel permissions, making sure that people can't get into channels they shouldn't be able to
**/
bool init_net()
{
	// Initialize SDL_net
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		return false;
	}
	// Open a socket
	if (!(sd = SDLNet_UDP_Open(2000)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		return false;
	}
	// Resolve server name
	if (SDLNet_ResolveHost(&srvadd, "127.0.0.1", atoi("3000")) == -1)
	{
		fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", "127.0.0.1", atoi("3000"), SDLNet_GetError());
		return false;
	}
	// Make space for the packet
	if (!(p = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		return false;
	}
	p->address.host = srvadd.host;	// Set the destination host
	p->address.port = srvadd.port;	// And destination port
	return true;
}

int main(int argc, char** argv)
{
	if( init_net() == false )
    {
        return 1;
    }

	// Engine vars
	fps = 30;
	cur_fps = 0;

	// Initialize the game
	Timer fpsTimer;
	Game game;

	// Call the game loop
	for (;;)
	{
		fpsTimer.Start();

		// Execute a frame's worth of activity
		// run a step, reply to requests
		if(game.LoopEvents()) break;
		if(game.LoopLogic()) break;

		// Manage FPS
		if (fpsTimer.GetTime() < 1000/fps)
		{
			SDL_Delay((1000/fps) - fpsTimer.GetTime());
		}
		cur_fps = 1000/fpsTimer.GetTime();
		// printf("CurFPS: %i \n", cur_fps);
	}

	fpsTimer.Stop();

	// Shut down the game
	return 0;
}
