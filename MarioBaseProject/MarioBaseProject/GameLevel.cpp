#include <SDL.h>
#include "GameLevel.h"
#include "CharacterMario.h"
#include "ScreenManager.h"
#include "FinishPoint.h"
#include "Constants.h"
#include "Map.h"
#include "Input.h"
#include "ScoreUI.h"

GameLevel::GameLevel(SDL_Renderer* renderer, const std::string& mapName) : BaseLevel(renderer, mapName)
{
	scoreUi = new ScoreUI(this, Vector2D(50, SCREEN_HEIGHT - 56), "Images/ScoreUI.png");
	
	SDL_SetWindowSize(ScreenManager::GetInst()->GetWindow(), SCREEN_WIDTH, SCREEN_HEIGHT);
	
	SetupLevel();
}

GameLevel::~GameLevel()
{
	delete scoreUi;
}

void GameLevel::Draw()
{
	BaseLevel::Draw();
	scoreUi->Draw();
}

void GameLevel::Update(float deltaTime)
{
	second += deltaTime;

	if (second > 1.f && GetMario()->IsAlive())
	{
		gameTime--;

		scoreUi->UpdateTime(gameTime);
		
		if (gameTime <= 0.f)
		{
			ScreenManager::GetInst()->ChangeScreen(SCREEN_LEVEL);
			return;
		}

		second = 0.f;
	}
	
	
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

void GameLevel::AddScore(int amount)
{
	score += amount;
	scoreUi->UpdateScore(score);
}

void GameLevel::SetupLevel()
{
	BaseLevel::SetupLevel();
	ScreenManager::GetInst()->SetCameraPos(Vector2D(map->GetMario()->GetPosition().x - 64.f, 0.f));
}
