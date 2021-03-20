#include <SDL.h>
#include "GameLevel.h"
#include "CharacterMario.h"
#include "ScreenManager.h"
#include "FinishPoint.h"
#include "Constants.h"
#include "Map.h"
#include "Input.h"

GameLevel::GameLevel(SDL_Renderer* renderer, const std::string& mapName) : BaseLevel(renderer, mapName)
{
	SDL_SetWindowSize(ScreenManager::GetInst()->GetWindow(), SCREEN_WIDTH, SCREEN_HEIGHT);
	
	SetupLevel();
}

GameLevel::~GameLevel()
{
}

void GameLevel::Draw()
{
	BaseLevel::Draw();
}

void GameLevel::Update(float deltaTime)
{
	if (Input::WasKeyDown(Key_K))
	{
		ScreenManager::GetInst()->ChangeScreen(SCREEN_EDITOR, currentMapName);
		return;
	}

	map->Update(deltaTime);
}

CharacterMario* GameLevel::GetMario()
{
	return map->GetMario();
}

void GameLevel::SetupLevel()
{
	BaseLevel::SetupLevel();
	ScreenManager::GetInst()->SetCameraPos(Vector2D(map->GetMario()->GetPosition().x - 64.f, 0.f));
}