#include <SDL.h>
#include "LevelEditor.h"
#include "Constants.h"
#include "Input.h"
#include "EditorMenu.h"
#include "Map.h"
#include "ScreenManager.h"

LevelEditor::LevelEditor(SDL_Renderer* renderer, const std::string& mapName) : BaseLevel(renderer, mapName)
{
	SDL_SetWindowSize(ScreenManager::GetWindow(), SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT);

	map->SetIsEditing(true);
	tileSelector = new EditorMenu(map);
	SetupLevel();
}

LevelEditor::~LevelEditor()
{
	delete map;
	map = nullptr;

	delete tileSelector;
	tileSelector = nullptr;
}

bool LevelEditor::SetupLevel()
{
	return false;
}

void LevelEditor::Draw()
{
	BaseLevel::Draw();
	
	if (tileSelector != nullptr)
		tileSelector->Draw();
}

void LevelEditor::Update(float deltaTime)
{
	if (Input::WasKeyDown(Key_T))
		map->SaveMap("TestMap.txt");

	if (Input::WasKeyDown(Key_Y))
		map->LoadMap("TestMap.txt");

	if (Input::WasKeyDown(Key_KP_PLUS))
		map->ChangeLength(map->GetLength() + (10 * TILE_SIZE));

	if (Input::WasKeyDown(Key_KP_MINUS))
		map->ChangeLength(map->GetLength() - (10 * TILE_SIZE));
	
	tileSelector->Update(deltaTime);

	Vector2D cameraPos = ScreenManager::GetCameraPos();

	if (Input::IsKeyDown(Key_D))
	{
		ScreenManager::SetCameraPos(Vector2D(cameraPos.x + TILE_SIZE, 0));
		
		if (cameraPos.x + SCREEN_WIDTH >= map->GetLength()) // TODO: replace SCREEN_WIDTH * 1.5 with level length when maps done!!
			ScreenManager::SetCameraPos(Vector2D(map->GetLength() - SCREEN_WIDTH, 0.f));
	}
	else if (Input::IsKeyDown(Key_A))
	{
		ScreenManager::SetCameraPos(Vector2D(cameraPos.x - TILE_SIZE, 0));
		
		if (cameraPos.x <= 0)
			ScreenManager::SetCameraPos(Vector2D(0.f, 0.f));
	}
}