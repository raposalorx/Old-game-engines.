#ifndef MAP_H
#define MAP_H

#include <vector>

#include "tile.h"
#include "object.h"

using namespace std;

class Map
{
	public:
		Map();
		~Map();

		// Tile functions
		void Resize(int new_w, int new_h);
		int GetW();
		int GetH();

		// Object functions
		int GetObjectCount();
		Object* AddObject(int type, int x, int y);
		Object* GetObject(int object);

		// Object type functions
		int GetObjectTypeCount();
		Object* AddObjectType();
		Object* GetObjectType(int object_type);
	protected:
	private:
		int w, h;
		vector<Object> objectDB, objecttypeDB;
};

#endif
