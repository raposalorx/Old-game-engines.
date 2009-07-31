#include "map.h"

Map::Map()
{
	w = 1;
	h = 1;
}

Map::~Map()
{
}

// --------------------------------------------------
// Tile functions
// --------------------------------------------------

void Map::Resize(int new_w, int new_h)
{
	w = new_w;
	h = new_h;
}


int Map::GetW()
{
	return w;
}

int Map::GetH()
{
	return h;
}

// --------------------------------------------------
// Object functions
// --------------------------------------------------

int Map::GetObjectCount()
{
	return objectDB.size();
}

Object* Map::AddObject(int type, int x, int y)
{
	/*// If the type does not exist, return NULL
	if (type >= objecttypeDB.size())
		return NULL;

	// Create a new object, and initialize its values
	objectDB.resize(objectDB.size()+1);
	Object* object = &objectDB.back();
	Object* object_type = &objecttypeDB[type];

	object->x = x;
	object->y = y;
	object->vel_mag = 0;
	object->vel_dir = 0;
	object->vel_max = object_type->vel_max;
	object->texture = object_type->texture;
	object->Step = object_type->Step;

	// Return the new object
	return object;*/
	return NULL;
}

Object* Map::GetObject(int object)
{
	return NULL;//&objectDB[object];
}

// --------------------------------------------------
// Object type functions
// --------------------------------------------------

int Map::GetObjectTypeCount()
{
	return objecttypeDB.size();
}

Object* Map::AddObjectType()
{
	// Create a new object type
	objecttypeDB.resize(objecttypeDB.size()+1);

	return &objecttypeDB.back();
}

Object* Map::GetObjectType(int object_type)
{
	return &objecttypeDB[object_type];
}
