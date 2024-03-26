#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Graphics.h>
#include <Globals.h>

#include <string>
#include <iostream>

//Starts up SDL and creates window
bool Graphics::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow(GLOBALS::GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GLOBALS::SCREEN_WIDTH, GLOBALS::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	return success;
}

SDL_Texture* Graphics::loadTexture(SDL_Surface* textureSurface)
{
	return SDL_CreateTextureFromSurface(renderer, textureSurface);
}

//Frees media and shuts down SDL
void Graphics::close()
{
	//Destroy window
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}