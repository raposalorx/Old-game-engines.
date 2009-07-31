#include "state_game.h"

State_Game::State_Game()
{
	// Create the Lua environment
	init_lua();

	// lua test code
	// if (luaL_loadfile(LuaState, "./test.lua") || lua_pcall(LuaState, 0, 0, 0))
	// {
	// 	fprintf(stderr, "%s", lua_tostring(LuaState, -1));
	// 	lua_pop(LuaState, 1);  /* pop error message from the stack */
	// }

	// Send the event to load the UI
	SendEvent("UI_LOAD");

	// Initialize the screen surface
	// screen = SDL_CreateRGBSurface(SDL_SWSURFACE, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
}

State_Game::~State_Game()
{
	// Send the event to shut down the UI
	SendEvent("UI_QUIT");

    // Destroy the Lua environment
    uninit_lua();/// NOTE: lua crashes the game at this point, but only if you move around. tracked via debug

    // Free the screen surface
	// SDL_FreeSurface(screen);

	// Empty obj_surfaceDB
	obj_surfaceDB[LAYER_NORMAL].clear();
}

void State_Game::Event()
{
	// message processing loop
	while (SDL_PollEvent(&event))
	{
		// check for messages
		switch (event.type)
		{
			// exit if the window is closed
		case SDL_QUIT:
			next_state = STATE_EXIT;
			break;

			// check for keypresses
		case SDL_KEYDOWN:
			{
				string id = itoa(ID);
				//printf("%c\n", (char)event.key.keysym.unicode);
				// exit if ESCAPE is pressed
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					SendUDP(strcat((char*)id.c_str(), ":logout"));
					next_state = STATE_LOGIN;
				}
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					SendUDP(strcat((char*)id.c_str(), ":DOWN"));
				}
				if (event.key.keysym.sym == SDLK_UP)
				{
					SendUDP(strcat((char*)id.c_str(), ":UP"));
				}
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					SendUDP(strcat((char*)id.c_str(), ":LEFT"));
				}
				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					SendUDP(strcat((char*)id.c_str(), ":RIGHT"));
				}
				break;
			}
		} // end switch
	} // end of message processing
	char* data;
	if ((data = GetUDP())!=NULL)//gets servers beings list
	{
		vector<string> beings;
		StringExplode(data, ";", &beings);// breaks up by id
		beingDB.clear();
		for(int i = 0; i < beings.size(); i++)
		{
			vector<string> being;
			StringExplode(beings[i], ":", &being);// breaks up being vars
			beingDB.push_back(*(new Being));// adds a new being to the screen with given vars for each being on the server
			beingDB[beingDB.size()-1].x = atoi(being[1].c_str());
			beingDB[beingDB.size()-1].y = atoi(being[2].c_str());
		}
	}
}

bool State_Game::Step()
{
	SendEvent("UI_STEP");
	return false;
}

void State_Game::Draw()
{
	Object_Surface* surface;
	// Print out each drawable object
	// int size = obj_surfaceDB[LAYER_NORMAL].size();
	for (int aa = 0; aa < beingDB.size(); aa++)
	{
		// surface = obj_surfaceDB[LAYER_NORMAL][aa];
		glLoadIdentity();
		
		glTranslatef( beingDB[aa].x, beingDB[aa].y, 0 );

	    // Bind the texture to which subsequent calls refer to
	    glBindTexture( GL_TEXTURE_2D, textureDB[0].texture );

	    glBegin( GL_QUADS );

		glTexCoord2f( 0, 0 ); 
			glVertex3f( 0, 0, 0 );
		glTexCoord2f( 0, (textureDB[0].height/textureDB[0].origheight)); 
			glVertex3f( 0, textureDB[0].height, 0 );
		glTexCoord2f( (textureDB[0].width/textureDB[0].origwidth), (textureDB[0].height/textureDB[0].origheight) ); 
			glVertex3f( textureDB[0].width, textureDB[0].height, 0 );
		glTexCoord2f( (textureDB[0].width/textureDB[0].origwidth), 0 ); 
			glVertex3f( textureDB[0].width, 0, 0 );
		glEnd();

	}
}
