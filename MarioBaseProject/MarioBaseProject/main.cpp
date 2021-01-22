#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Constants.h"

bool InitSDL();
void CloseSDL();

SDL_Window* window = nullptr;

int main(int argc, char* args[])
{
	if (InitSDL())
		SDL_Delay(5000);

	CloseSDL();
	
	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL did not initialise. ERROR: " << SDL_GetError();
		return false;
	}

	window = SDL_CreateWindow("Mario",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Window was not created. Error: " << SDL_GetError();
		return false;
	}
	
	return true;
}

void CloseSDL()
{
	SDL_DestroyWindow(window);
	window = nullptr;

	IMG_Quit();
	SDL_Quit();
}
