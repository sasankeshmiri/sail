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

	public:
		SDL_Renderer* renderer{NULL};
		bool init();
		void close();
};

#endif