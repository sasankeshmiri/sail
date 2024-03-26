#ifndef GRAPHICS_H
#define GRAPHICS_H

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

class Graphics
{
	private:
		SDL_Window* window{NULL};
		SDL_Surface* surface{NULL};
		SDL_Texture* texture{NULL};

	public:
		SDL_Renderer* renderer{NULL};
		bool init();
		SDL_Texture* loadTexture(SDL_Surface*);
		void close();
};

#endif