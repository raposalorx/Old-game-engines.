#include "object_sidebar.h"

Object_Sidebar::Object_Sidebar()
{
	// Grab this object's sprite
	if (tree_textures.Search("spr_sidebar"))
		t_sidebar = (Texture*)tree_textures.GetLast();
	else
		t_sidebar = NULL;
}

Object_Sidebar::~Object_Sidebar()
{
}

void Object_Sidebar::Step()
{
}

void Object_Sidebar::Draw()
{
	if (t_sidebar != NULL)
		t_sidebar->Draw(screen_w - t_sidebar->GetW(), 0, 0);

	const int MINIMAP_SIZE = 126;
	
	// Draws all objects in the mini map
	for (int aa = 0; aa < objectDB.size()-1; aa++)///TODO: Find a better way to exclude the sidebar
	{
		glLoadIdentity();
		glTranslatef((screen_w-127), 1, 0);
		glBegin(GL_QUADS);
			glColor4f(1.0, 0.0, 1.0, 1.0);
			glVertex3f(objectDB[aa]->GetX()/(game_w/MINIMAP_SIZE), objectDB[aa]->GetY()/(game_w/MINIMAP_SIZE), 0);
			glVertex3f(objectDB[aa]->GetX()/(game_w/MINIMAP_SIZE), objectDB[aa]->GetY()/(game_w/MINIMAP_SIZE)+objectDB[aa]->GetH()/(game_w/MINIMAP_SIZE), 0);
			glVertex3f(objectDB[aa]->GetX()/(game_w/MINIMAP_SIZE)+objectDB[aa]->GetW()/(game_w/MINIMAP_SIZE), objectDB[aa]->GetY()/(game_w/MINIMAP_SIZE)+objectDB[aa]->GetH()/(game_w/MINIMAP_SIZE), 0);
			glVertex3f(objectDB[aa]->GetX()/(game_w/MINIMAP_SIZE)+objectDB[aa]->GetW()/(game_w/MINIMAP_SIZE), objectDB[aa]->GetY()/(game_w/MINIMAP_SIZE), 0);
		glEnd();
	}
	
	// Draws the screen bounds in the mini map
	glLoadIdentity();
	glTranslatef((screen_w-MINIMAP_SIZE+1)+(screen_x/(game_w/MINIMAP_SIZE)), 1+(screen_y/(game_w/MINIMAP_SIZE)), 0);
	glBegin(GL_LINE_LOOP);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, MINIMAP_SIZE/(game_h/screen_h), 0);
		glVertex3f(MINIMAP_SIZE/(game_w/screen_w), MINIMAP_SIZE/(game_h/screen_h), 0);
		glVertex3f(MINIMAP_SIZE/(game_w/screen_w), 0, 0);
	glEnd();
	
	// Draw the selected unit(s) selection image
//	int size = min(16, u_selected.size());
//	if (size == 1)
	{
	}
//	else
//		for (int aa = 0; aa < size; aa++)
		{
		}
}

// Factory function
Object_Sidebar* CreateObject(Object_Sidebar* new_object, const char* name)
{
	objectDB.push_back(new_object);
	if (name != NULL)
		tree_objects.AddString(name, new_object, 0);
	return new_object;
}
