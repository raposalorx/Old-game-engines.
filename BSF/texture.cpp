#include "texture.h"

Texture::Texture()
{
	h = 0;
	w = 0;
	texture = 0;
	bitmask = NULL;
}

Texture::~Texture()
{
	if (texture != 0)
		glDeleteTextures(1, &texture);
}

void Texture::LoadImage(char* filename)
{
	GLenum texture_format;
	GLint color_count;

	// Load and convert the surface
	SDL_Surface* surface = IMG_Load(filename);

	// Set the raw dimensions for the loaded image
	h = surface->h;
	w = surface->w;

	// Calculate the OpenGL dimensions of the texture (2^x)
	int gl_h = pow(2, ceil(log(h)/log(2)));
	int gl_w = pow(2, ceil(log(w)/log(2)));

	// Reset the bitmask
	delete bitmask;
	bitmask = new bool[w * h];

    // Get the number of channels in the SDL surface
	color_count = surface->format->BytesPerPixel;
	switch (color_count)
	{
	case 4:	// contains an alpha channel
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
		// Form a bitmask from
		for (int aa = 0; aa < h; aa++)
			for (int bb = 0; bb < w; bb++)
				bitmask[w * aa + bb] = ((Uint32*)surface->pixels)[w * aa + bb] * 0xff000000 == 0;
		break;
	case 3:	// no alpha channel
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
		break;
	default:
		printf("Warning: the image is not truecolor, this will probably break\n");
		/// TODO: handle this error
	}

	if (texture != 0)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}
	glGenTextures(1, &texture);

	// Bind the texure to the target map
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set the texture's stretching properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Pad the surface if needed, and store it
	if (gl_h == h and gl_w == w)
	{
		// Edit the texture object's image data using information from SDL_Surface
		glTexImage2D(GL_TEXTURE_2D, 0, color_count, w, h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else
	{
		// Pad the texture
		SDL_LockSurface(surface);
		Uint32* pixels = (Uint32*)surface->pixels;
		Uint32* padded_pixels = new Uint32[gl_w * gl_h];
		for (int aa = 0; aa < h; aa++)
		{
			for (int bb = 0; bb < w; bb++)
				padded_pixels[gl_w * aa + bb] = pixels[w * aa + bb];
			for (int bb = w; bb < gl_w; bb++)
				padded_pixels[gl_w * aa + bb] = 0x00000000;
		}
		for (int aa = h; aa < gl_h; aa++)
		{
			for (int bb = 0; bb < gl_w; bb++)
				padded_pixels[gl_w * aa + bb] = 0x00000000;
		}

		w = gl_w;
		h = gl_h;

		// Edit the texture object's image data using information from SDL_Surface
		glTexImage2D(GL_TEXTURE_2D, 0, color_count, w, h, 0, texture_format, GL_UNSIGNED_BYTE, padded_pixels);
	}

	// Free the surface
	SDL_FreeSurface(surface);

	// Reset the texture binding
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Texture::Draw(int x, int y, double rot)
{
	glLoadIdentity();

	// Bind the texture to which subsequent calls refer to
	glBindTexture(GL_TEXTURE_2D, texture);

	// Transform the image
	glRotatef(rot, 0.0, 0.0, 1.0);
	glTranslatef(x, y, 0);

	// Draw the quad
	glBegin(GL_QUADS);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(0, h, 0);
		glTexCoord2f(1, 1);
		glVertex3f(w, h, 0);
		glTexCoord2f(1, 0);
		glVertex3f(w, 0, 0);
	glEnd();

	// Reset the texture binding
	glBindTexture(GL_TEXTURE_2D, NULL);
}

int Texture::GetW()
{
	return w;
}

int Texture::GetH()
{
	return h;
}

bool* Texture::GetBitMask()
{
	return bitmask;
}
