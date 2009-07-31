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
Object_Sidebar* CreateObject(Object_Sidebar* new_object, char* name)
{
	objectDB.push_back(new_object);
	tree_objects.AddString(name, new_object, 0);
	return new_object;
}
