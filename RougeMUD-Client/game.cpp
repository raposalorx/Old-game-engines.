#include "game.h"

Game::Game()
{
    // Load images
	string filename;
	fstream fin("data/img.init", fstream::in);
	while (!fin.eof())
	{
		getline(fin, filename);
		vector<string> split;
		//split the string into parts: name width height
		StringExplode(filename.c_str(), " ", &split);
		filename = split[0];
		
	    SDL_Surface *surface; // Gives us the information to make the texture
		GLenum texture_format;
		GLint  nOfColors;
	    if ( (surface = SDL_LoadBMP(filename.c_str())) ) { 
			textureDB.push_back(*(new Texture));
	        // Check that the image's width is a power of 2
	        if ( (surface->w & (surface->w - 1)) != 0 ) {
	            printf("warning: image's width(%i) is not a power of 2\n", surface->w);
	        }

	        // Also check if the height is a power of 2
	        if ( (surface->h & (surface->h - 1)) != 0 ) {
	            printf("warning: image's height(%i) is not a power of 2\n", surface->h);
	        }

			// get the number of channels in the SDL surface
	        nOfColors = surface->format->BytesPerPixel;
	        if (nOfColors == 4)     // contains an alpha channel
	        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
	        } else if (nOfColors == 3)     // no alpha channel
	        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
	        } else {
	                printf("warning: the image is not truecolor..  this will probably break\n");
	                // this error should not go unhandled
	        }
			
	        // Have OpenGL generate a texture object handle for us
	        glGenTextures( 1, &textureDB[textureDB.size()-1].texture );

	        // Bind the texture object
	        glBindTexture( GL_TEXTURE_2D, textureDB[textureDB.size()-1].texture );

	        // Set the texture's stretching properties
	        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	        // Edit the texture object's image data using the information SDL_Surface gives us
	        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels );
			
			//set dimensions for the loaded images
			textureDB[textureDB.size()-1].origwidth = surface->w;
			textureDB[textureDB.size()-1].origheight = surface->h;
			textureDB[textureDB.size()-1].width = atoi(split[1].c_str());
			textureDB[textureDB.size()-1].height = atoi(split[2].c_str());
	
	    } 
	    else {
	        printf("SDL could not load image: %s\n", SDL_GetError());
	        SDL_Quit();
	        throw IMG_LOAD_EXCEPTION;
	    }    
	

	    // Free the SDL_Surface only if it was successfully created
	    if ( surface ) { 
	        SDL_FreeSurface( surface );
	    }
	}

	// Create the State objects, and make the Menu active
	game_state = new State_Login();
	cur_state = STATE_LOGIN;
	next_state = STATE_NULL;
}

Game::~Game()
{
    // Free loaded bitmaps
    for (unsigned int aa = 0; aa < textureDB.size(); aa++)
    {
		glDeleteTextures( 1, &textureDB[aa].texture );
    }
    
    printf("Exited cleanly\n");
}

void Game::LoopEvents()
{
	game_state->Event();
}

bool Game::LoopLogic()
{
	return game_state->Step();
}

bool Game::ChangeState()
{
	if (next_state != STATE_NULL)
	{
		if (next_state != STATE_EXIT)
		{
			delete game_state;
		}
		else
		{
			return true;
		}

		switch (next_state)
		{
		case STATE_LOGIN:
			game_state = new State_Login();
			break;
		case STATE_GAME:
			game_state = new State_Game();
			break;
		}

		cur_state = next_state;
		next_state = STATE_NULL;
	}
	return false;
}

void Game::LoopRender()
{

	// Draw from the state
	glClear( GL_COLOR_BUFFER_BIT );
	
	game_state->Draw();
	
	glLoadIdentity();
    SDL_GL_SwapBuffers();

}

const char* IMG_EXCEPTION::what() const throw()
{
	return "Image does not exist";
}