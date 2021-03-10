#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "Input.h"

bool InitSDL();
void CloseSDL();
bool Update();
void Render();

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
GameScreenManager* screenManager;

Uint32 oldTime;

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		bool quit = false;
		screenManager = new GameScreenManager(renderer, ScreenType::SCREEN_LEVEL1);
		oldTime = SDL_GetTicks();
		
		while (!quit)
		{
			Render();
			quit = Update();		
		}
	}

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

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	int imageFlags = IMG_INIT_PNG;
	
	if (!(IMG_Init(imageFlags)& imageFlags))
	{
		std::cout << "SDL_Image could not initialise. Error: " << SDL_GetError();
		return false;
	}

	
	return true;
}

void CloseSDL()
{
	delete screenManager;
	screenManager = nullptr;
	
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	
	SDL_DestroyWindow(window);
	window = nullptr;

	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	Uint32 newTime = SDL_GetTicks();
	SDL_Event event;
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		return true;
		break;
	}

	Input::GetInst()->Update();
	screenManager->Update((float)(newTime - oldTime) / 1000.f, event);
	oldTime = newTime;
	
	return false;
	
}

void Render()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	screenManager->Render();
	SDL_RenderPresent(renderer);
}
