#include "state_game.h"

State_Game::State_Game()
{
	// Load textures
	textureDB.resize(3);
	textureDB[0].LoadImage((char*)"./images/hestia.png");
	textureDB[1].LoadImage((char*)"./images/minimap.png");
	textureDB[2].LoadImage((char*)"./images/dwarf.png");

	// Textures
	tree_textures.AddString("spr_hestia", &textureDB[0], 1);
	tree_textures.AddString("spr_sidebar", &textureDB[1], 1);
	tree_textures.AddString("spr_dwarf", &textureDB[2], 1);

	// Environment vars
	mouse_x = 0;
	mouse_y = 0;
	screen_w = 800;
	screen_h = 600;

	// Objects
	Object_Unit* unit = CreateObject(new Object_Ship, NULL);
	CreateObject(new Object_Sidebar, "UI_SIDEBAR");
	unit->Move(10, 10);
	unit->SetTeam(1);
}

State_Game::~State_Game()
{
	int size = objectDB.size();
	for (int aa = 0; aa < size; aa++)
	{
		delete objectDB[aa];
	}
}

void State_Game::Event()
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
				// Exit if ESCAPE is pressed
				if (event.key.keysym.sym == SDLK_ESCAPE)
					state_next = STATE_EXIT;
			}
			break;
			// Check for mouse movement
		case SDL_MOUSEMOTION:
			mouse_x = event.motion.x;
			mouse_y = event.motion.y;
			break;
			// Check for mouse button presses
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		}
	}
}

void State_Game::Logic()
{
	int size = objectDB.size();
	for (int aa = 0; aa < size; aa++)
	{
		objectDB[aa]->Step();
	}
	/*int size = map->GetObjectCount();
	for (int aa = 0; aa < size; aa++)
	{
		Object* object = map->GetObject(aa);
		object->Step(object);
	}

	// Check key states
	Uint8 *keystates = SDL_GetKeyState(NULL);

	int view_move;
	if (keystates[SDLK_LSHIFT] | keystates[SDLK_RSHIFT])
		view_move = 10;
	else
		view_move = 1;
	if (keystates[SDLK_UP])
		view_y -= view_move;
	if (keystates[SDLK_DOWN])
		view_y += view_move;
	if (keystates[SDLK_RIGHT])
		view_x += view_move;
	if (keystates[SDLK_LEFT])
		view_x -= view_move;

	// Make sure the viewport coordinates are valid
	if (view_x < 0)
		view_x = 0;
	if (view_x > view_x_max)
		view_x = view_x_max;
	if (view_y < 0)
		view_y = 0;
	if (view_y > view_y_max)
		view_y = view_y_max;*/
}

void State_Game::Render()
{
	// Draw the objects
	int size = objectDB.size();
	for (int aa = 0; aa < size; aa++)
	{
		objectDB[aa]->Draw();
	}

	/*// Draw the objects
	int size = map->GetObjectCount();
	for (int aa = 0; aa < size; aa++)
	{
		Object* object = map->GetObject(aa);
		if ((object->x + textureDB[object->texture].GetW() >= view_x) and
			(object->y + textureDB[object->texture].GetH() >= view_y) and
			(object->x < view_x + 800) and
			(object->y < view_y + 600))
		{
			textureDB[0].Draw(object->x - view_x, object->y - view_y, 30);
		}
	}

	// Draw the minimap

	// Border
	textureDB[1].Draw(800-128, 0, 0);

	// Blips
	int map_w = map->GetW() * 16, map_h = map->GetH() * 16;
	size = map->GetObjectCount();

	// Draw the points
	glPointSize(1.0);
	glLoadIdentity();
	glBegin(GL_POINTS);
	for (int aa = 0; aa < size; aa++)
	{
		Object* object = map->GetObject(aa);
		glColor4f(1.0, 0.0, 0.0, 1.0);
		int x = (double)object->x / (double)map_w * 126.0 + 800.0 - 126.0, y = (double)object->y / (double)map_h * 126.0 + 2.0;
		printf("%i, %i\n", x, y);
		if (x < 792 and y < 120 and x > 673 and y > 1)
			glVertex3f(x, y, 0);
	}
	glEnd();

	// Draw the viewport's silhouette on the minimap
	glTranslatef((int)((double)view_x / (double)map_w * 126.0 + 800.0 - 126.0), (int)((double)view_y / (double)map_h * 126.0 + 2.0), 0);
	glBegin(GL_LINE_LOOP);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex3i(0, 0, 0);
		glVertex3i(0, mini_view_h, 0);
		glVertex3i(mini_view_w, mini_view_h, 0);
		glVertex3i(mini_view_w, 0, 0);
	glEnd();
	glBegin(GL_POINTS);
		glVertex3i(0, 0, 0);
	glEnd();

	/// TODO: make it render the minimap background as well*/
}

Enum_State State_Game::ChangeState()
{
	return state_next;
}
