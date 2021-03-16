#pragma once
#include <SDL.h>
#include <string>
#include "GameObject.h"
#include "Commons.h"

class MainMenu;
class BaseLevel;
class Texture2D;

class ScreenManager : public GameObject
{
	static ScreenManager* inst;
	
	Texture2D* gameTileMap;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Vector2D* cameraPos;
	BaseLevel* currentLevel;
	
	MainMenu* mainMenu;
	bool inMainMenu = true;
	
public:
	ScreenManager(SDL_Window* window, SDL_Renderer* renderer, ScreenType screenType);
	~ScreenManager();

	static ScreenManager* GetInst() { return inst; }

	void Draw() override;
	void Update(float deltaTime) override;
	
	void ChangeScreen(ScreenType newScreen, std::string mapName = "");

	void SetCameraPos(Vector2D newCameraPos) { *cameraPos = newCameraPos; }
	Vector2D GetCameraPos() { return *cameraPos; }
	
	SDL_Renderer* GetRenderer() { return renderer; }
	SDL_Window* GetWindow() { return window; }
	Texture2D* GetTileMap();

	int GetCurrentMapLength();
	BaseLevel* GetCurrentLevel() { return currentLevel; }
};