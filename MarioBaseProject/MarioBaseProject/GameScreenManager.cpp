#include "GameScreenManager.h"
#include "GameScreenLevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, ScreenType startScreen)
{
	this->renderer = renderer;
	currentGameScreen = nullptr;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	renderer = nullptr;

	delete currentGameScreen;
	currentGameScreen = nullptr;
}

void GameScreenManager::Render()
{
	currentGameScreen->Render();
	
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	currentGameScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(ScreenType newScreen)
{
	GameScreenLevel1* tempScreen;
	
	if (currentGameScreen != nullptr)
	{
		delete currentGameScreen;
	}

	switch (newScreen)
	{
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(renderer);
		currentGameScreen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;

	default:;
	}
}
