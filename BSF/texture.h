#ifndef TEXTURE_H
#define TEXTURE_H

#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

class Texture
{
	public:
		Texture();
		~Texture();

		void LoadImage(char* filename);
		void Draw(int x, int y, double rot);
		int GetW();
		int GetH();
		bool* GetBitMask();
	protected:
	private:
		int h, w;
		GLuint texture;
		bool* bitmask;
};

#endif
