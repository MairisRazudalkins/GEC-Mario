#include "ScreenManager.h"

#include <iostream>

#include "BaseLevel.h"
#include "GameLevel.h"
#include "LevelEditor.h"
#include "Texture2D.h"
#include "Constants.h"
#include "MainMenu.h"

ScreenManager* ScreenManager::inst = nullptr;

ScreenManager::ScreenManager(SDL_Window* window, SDL_Renderer* renderer, ScreenType screenType)
{
	inst = this;
	cameraPos = new Vector2D(0, 0);
	
	this->window = window;
	this->renderer = renderer;
	
	mainMenu = new MainMenu(this);	
	//ChangeScreen(screenType);
}

ScreenManager::~ScreenManager()
{
	renderer = nullptr;

	delete mainMenu;
	mainMenu = nullptr;

	delete currentLevel;
	currentLevel = nullptr;

	delete gameTileMap;
	gameTileMap = nullptr;
}

void ScreenManager::Draw()
{
	if (inMainMenu)
		mainMenu->Draw();
	else
		currentLevel->Draw();
}

void ScreenManager::Update(float deltaTime)
{
	if (inMainMenu)
		mainMenu->Update(deltaTime);
	else
		currentLevel->Update(deltaTime);
}

void ScreenManager::ChangeScreen(ScreenType newScreen, std::string mapName)
{
	inMainMenu = false;
	
	if (currentLevel != nullptr)
	{
		delete currentLevel;
		currentLevel = nullptr;
	}


	if (newScreen == SCREEN_MENU)
		inMainMenu = true;
	else if (newScreen == SCREEN_LEVEL)
		currentLevel = new GameLevel(renderer, mapName);
	else if (newScreen == SCREEN_EDITOR)
		currentLevel = new LevelEditor(renderer, mapName);
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
