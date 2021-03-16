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
	delete characterMario;
	characterMario = nullptr;

	delete finishPoint;
	finishPoint = nullptr;
}

void GameLevel::Draw()
{
	BaseLevel::Draw();

	if (ScreenManager::GetInst()->GetCameraPos().x + SCREEN_WIDTH > finishPoint->GetPosition().x)
		finishPoint->Draw();
	
	characterMario->Draw();
}

void GameLevel::Update(float deltaTime)
{
	map->Update(deltaTime);
	
	if (ScreenManager::GetInst()->GetCameraPos().x + SCREEN_WIDTH > finishPoint->GetPosition().x)
		finishPoint->Update(deltaTime);
	
	characterMario->Update(deltaTime);

	if (characterMario->GetPosition().y > SCREEN_HEIGHT)
	{
		characterMario->KillCharacter();
		ScreenManager::GetInst()->ChangeScreen(SCREEN_LEVEL, currentMapName);
		return;
	}

	if (Input::WasKeyDown(Key_K))
	{
		ScreenManager::GetInst()->ChangeScreen(SCREEN_EDITOR, currentMapName);
		return;
	}
	
	Vector2D cameraPos = ScreenManager::GetInst()->GetCameraPos();
	
	if (cameraPos.x + SCREEN_WIDTH >= ScreenManager::GetInst()->GetCurrentMapLength())
		ScreenManager::GetInst()->SetCameraPos(Vector2D(ScreenManager::GetInst()->GetCurrentMapLength() - SCREEN_WIDTH, 0.f));
	else if ((cameraPos.x + SCREEN_WIDTH / 2) < characterMario->GetPosition().x)
		ScreenManager::GetInst()->SetCameraPos(Vector2D(characterMario->GetPosition().x - (SCREEN_WIDTH / 2), 0.f));
}

bool GameLevel::SetupLevel()
{
	characterMario = new CharacterMario(map->GetStartPos(), "Images/MarioSpriteSheet.png", map);
	finishPoint = new FinishPoint(map->GetEndPos(), "Images/TestTile.png", characterMario);
	
	ScreenManager::GetInst()->SetCameraPos(Vector2D(characterMario->GetPosition().x - 64.f, 0.f));

	return true;
}

