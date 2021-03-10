#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Commons.h"

class BaseLevel;

class ScreenManager : public GameObject
{
	static Texture2D* gameTileMap;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static Vector2D* cameraPos;
	static BaseLevel* currentLevel;
	
public:
	ScreenManager(SDL_Window* window, SDL_Renderer* renderer, ScreenType screenType);
	~ScreenManager();

	void Draw() override;
	void Update(float deltaTime) override;
	void ChangeScreen(ScreenType newScreen);

	static Vector2D GetCameraPos() { return *cameraPos; }
	static void SetCameraPos(Vector2D newCameraPos) { *cameraPos = newCameraPos; }
	static SDL_Renderer* GetRenderer() { return renderer; }
	static Texture2D* GetTileMap();
	static SDL_Window* GetWindow() { return window; }
	static int GetCurrentMapLength();
};