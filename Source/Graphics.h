#ifndef GRAPHICS_H
#define GRAPHICS_H

#define SDL_MAIN_HANDLED

#include <SDL_main.h>
#include <SDL_image.h>

#include <string>

class Graphics
{
	private:
		SDL_Window* window{NULL};
		SDL_Renderer* renderer{NULL};

		bool init();
		void close();

	public:
		void drawGraphics();
};

#endif