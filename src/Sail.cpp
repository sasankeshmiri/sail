// TODO 11: Include TutorialConfig.h
//#include "SailConfig.h"

#include <Globals.h>
#include <Graphics.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <iostream>
#include <numbers>
#include <cmath>

int main()
{
	Graphics graphics{};
	double playerXPos{GLOBALS::SCREEN_WIDTH/2};
	double playerYPos{GLOBALS::SCREEN_HEIGHT/2};
	bool playerThrottle{false};
	double playerRotation{90.0}; //Degrees

	//Start up SDL and create window
	if (!graphics.init())
	{
		std::cout << "Failed to initialize!" << std::endl;
	}
	else
	{
		//Main loop flag
		bool running{true};
		//Event handler
		SDL_Event e{};

		SDL_RWops* textureSource{SDL_RWFromFile(GLOBALS::PLAYERTEXTURE.c_str(), "r")};
		if (textureSource == NULL)
		{
			std::cout << "Failed to read image! SDL Error: " << SDL_GetError() << std::endl;
			running = false;
		}
		SDL_Surface* textureSurface{IMG_LoadSizedSVG_RW(textureSource, 30, 100)};
		if (textureSurface == NULL)
		{
			std::cout << "Failed to create surface from image! SDL Error: " << SDL_GetError() << std::endl;
			running = false;
		}
		SDL_Texture* playerTexture{SDL_CreateTextureFromSurface(graphics.renderer, textureSurface)};
		if (playerTexture == NULL)
		{
			std::cout << "Failed to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
			running = false;
		}
		SDL_Rect renderTarget{int(playerXPos), int(playerYPos), 30, 100};

		//While application is running
		while (running)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					running = false;
				}
				//User presses key
				else if(e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_ESCAPE)
					{
						running = false;
					}
					if (e.key.keysym.sym == SDLK_w)
					{
						playerThrottle = true;
					}
					if (e.key.keysym.sym == SDLK_s)
					{
						playerThrottle = false;
					}
				}
			}

			//Game activity
			//Move player if throttle is set
			if (playerThrottle)
			{
					playerYPos -= sin(playerRotation*std::numbers::pi/180.0)*0.5;
					playerXPos += cos(playerRotation*std::numbers::pi/180.0)*0.5;
			}

			//Clear screen
			SDL_SetRenderDrawColor(graphics.renderer, 0, 157, 196, 255); //Ocean blue
			SDL_RenderClear(graphics.renderer);

			//Draw player character
			renderTarget.x = int(playerXPos);
			renderTarget.y = int(playerYPos);
			SDL_RenderCopy(graphics.renderer, playerTexture, NULL, &renderTarget);

			//Update screen
			SDL_RenderPresent(graphics.renderer);
		}
	}

	//Free resources and close SDL
	graphics.close();
  return 0;
}
