#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

GameScreen::~GameScreen()
{
	renderer = nullptr;
}

void GameScreen::Render()
{
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{
}
