#pragma once
#include <SDL.h>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
	SDL_Renderer* renderer;
	GameScreen* currentGameScreen;
	
public:
	GameScreenManager(SDL_Renderer* renderer, ScreenType startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void ChangeScreen(ScreenType newScreen);
};