#include "ScreenManager.h"
#include "BaseLevel.h"
#include "GameLevel.h"
#include "LevelEditor.h"
#include "Texture2D.h"
#include "Constants.h"

Vector2D* ScreenManager::cameraPos = new Vector2D(0.f, 0.f);
BaseLevel* ScreenManager::currentLevel = nullptr;
SDL_Renderer* ScreenManager::renderer = nullptr;
Texture2D* ScreenManager::gameTileMap = nullptr;
SDL_Window* ScreenManager::window = nullptr;

ScreenManager::ScreenManager(SDL_Window* window, SDL_Renderer* renderer, ScreenType screenType)
{
	this->window = window;
	this->renderer = renderer;
	ChangeScreen(screenType);
}

ScreenManager::~ScreenManager()
{
	renderer = nullptr;

	delete currentLevel;
	currentLevel = nullptr;

	delete gameTileMap;
	gameTileMap = nullptr;
}

void ScreenManager::Draw()
{
	currentLevel->Draw();
}

void ScreenManager::Update(float deltaTime)
{
	currentLevel->Update(deltaTime);
}

void ScreenManager::ChangeScreen(ScreenType newScreen)
{
	BaseLevel* tempLevel;
	
	if (currentLevel != nullptr)
	{
		delete currentLevel;
	}
	
	switch (newScreen)
	{
	case SCREEN_LEVEL1:
		tempLevel = new GameLevel(renderer, "TestMap.txt");
		currentLevel = (BaseLevel*)tempLevel;
		tempLevel = nullptr;
		break;
	}
}

Texture2D* ScreenManager::GetTileMap()
{
	if (gameTileMap == nullptr)
	{
		gameTileMap = new Texture2D();
		gameTileMap->LoadTextureFromFile("Images/SpriteSheet.png");
	}

	return gameTileMap;
}

int ScreenManager::GetCurrentMapLength()
{
	return currentLevel != nullptr ? currentLevel->GetCurMapLength() : SCREEN_WIDTH;
}
