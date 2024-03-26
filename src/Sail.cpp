// TODO 11: Include TutorialConfig.h
//#include "SailConfig.h"

#include <Globals.h>
#include <Graphics.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <iostream>

int main()
{
	Graphics graphics{};
	int playerXPos{GLOBALS::SCREEN_WIDTH/2};
	int playerYPos{GLOBALS::SCREEN_HEIGHT/2};

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
				}
			}

			//Clear screen
			SDL_SetRenderDrawColor(graphics.renderer, 0, 157, 196, 255); //Ocean blue
			SDL_RenderClear(graphics.renderer);

			//Draw player character
			int playerSizeOffset{10};
			SDL_Color playerColor{255, 0, 0, 255};
			SDL_Vertex vertexTopCenter{{float(playerXPos), float(playerYPos-playerSizeOffset)}, playerColor, {1, 1}};
			SDL_Vertex vertexBottomLeft{{float(playerXPos-playerSizeOffset), float(playerYPos+playerSizeOffset)}, playerColor, {1, 1}};
			SDL_Vertex vertexBottomRight{{float(playerXPos+playerSizeOffset), float(playerYPos+playerSizeOffset)}, playerColor, {1, 1}};

			SDL_Vertex vertices[]{vertexTopCenter, vertexBottomLeft, vertexBottomRight};

			SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 255);

			SDL_RenderGeometry(graphics.renderer, NULL, vertices, 3, NULL, 0);

			//Update screen
			SDL_RenderPresent(graphics.renderer);
		}
	}

	//Free resources and close SDL
	graphics.close();
  return 0;
}
