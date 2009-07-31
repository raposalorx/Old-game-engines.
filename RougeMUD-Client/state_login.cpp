#include "state_login.h"

State_Login::State_Login()
{
	screen = SDL_CreateRGBSurface(SDL_SWSURFACE, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
}

State_Login::~State_Login()
{
	SDL_FreeSurface(screen);
}

void State_Login::Event()
{
	// printf("begin loop\n");
	while (SDL_PollEvent(&event))
	{
		// Check for messages
		switch (event.type)
		{
			// Exit if the window is closed
		case SDL_QUIT:
			next_state = STATE_EXIT;
			break;

			// Check for keypresses
		case SDL_KEYDOWN:
			{
				// Exit if ESCAPE is pressed
				if (event.key.keysym.sym == SDLK_ESCAPE)
					next_state = STATE_EXIT;

				// Switch state to game if ENTER is pressed
				if (event.key.keysym.sym == SDLK_RETURN)
				{
					SendUDP("login");
				}
				break;
			}
		}
	}
	// printf("mid loop\n");
	char* data;
	if ((data = GetUDP())!=NULL)
	{
		printf("len:%i\n", strlen(data));
		if(strlen(data)==1)//checks for id return
		{
			ID = atoi(data);
			next_state = STATE_GAME;
			printf("state->game\n");
		}
	}
	// printf("end loop\n");
}

bool State_Login::Step()
{
	return false;
}

void State_Login::Draw()
{
	
    glBindTexture( GL_TEXTURE_2D, textureDB[1].texture );

	glTranslatef( (WIDTH/2)-(textureDB[1].width/2), (HEIGHT/2)-(textureDB[1].height/2), 0 );

    glBegin( GL_QUADS );

	glTexCoord2f( 0, 0 ); 
		glVertex3f( 0, 0, 0 );
	glTexCoord2f( 0, (textureDB[1].height/textureDB[1].origheight)); 
		glVertex3f( 0, textureDB[1].height, 0 );
	glTexCoord2f( (textureDB[1].width/textureDB[1].origwidth), (textureDB[1].height/textureDB[1].origheight) ); 
		glVertex3f( textureDB[1].width, textureDB[1].height, 0 );
	glTexCoord2f( (textureDB[1].width/textureDB[1].origwidth), 0 ); 
		glVertex3f( textureDB[1].width, 0, 0 );
	
	glEnd();
	
}

