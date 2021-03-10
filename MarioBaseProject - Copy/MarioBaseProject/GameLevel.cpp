#include <SDL.h>
#include "GameLevel.h"
#include "CharacterMario.h"
#include "ScreenManager.h"
#include "Constants.h"

GameLevel::GameLevel(SDL_Renderer* renderer, const std::string& mapName) : BaseLevel(renderer, mapName)
{
	SetupLevel();
}

GameLevel::~GameLevel()
{
	delete testCharacter;
	testCharacter = nullptr;
}

void GameLevel::Draw()
{
	BaseLevel::Draw();
	
	testCharacter->Draw();
}

void GameLevel::Update(float deltaTime)
{
	testCharacter->Update(deltaTime);

	Vector2D cameraPos = ScreenManager::GetCameraPos();

	if (cameraPos.x + SCREEN_WIDTH >= ScreenManager::GetCurrentMapLength() * TILE_SIZE) // TODO: replace SCREEN_WIDTH * 1.5 with level length when maps done!!
		ScreenManager::SetCameraPos(Vector2D(ScreenManager::GetCurrentMapLength() * TILE_SIZE - SCREEN_WIDTH, 0.f));
	else if ((cameraPos.x + SCREEN_WIDTH / 2) < testCharacter->GetPosition().x)
		ScreenManager::SetCameraPos(Vector2D(testCharacter->GetPosition().x - (SCREEN_WIDTH / 2), 0.f));
}

bool GameLevel::SetupLevel()
{
	testCharacter = new CharacterMario(Vector2D(50.f, 250.f), "Images/Mario.png", map);

	return true;
}
