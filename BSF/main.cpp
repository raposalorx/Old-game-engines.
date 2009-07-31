#include "game.h"
#include "timer.h"

int main(int argc, char** argv)
{
	// Initialize the program
	bool cont = true;
	int fps = 30;
	Timer fpsTimer;
	Game game;

	if (game.Init())
	{
		// Main program loop
		while (cont)
		{
			fpsTimer.Start();

			game.Event();
			game.Logic();
			game.Render();
			cont = game.ChangeState();

			// Manage FPS
			if (fpsTimer.GetTime() < 1000/fps)
			{
				SDL_Delay((1000/fps) - fpsTimer.GetTime());
			}
			//double cur_fps = 1000/fpsTimer.GetTime();
			//printf("%f\n", cur_fps);
		}

		fpsTimer.Stop();
	}

	// Close down and clean up
	return 0;
}
