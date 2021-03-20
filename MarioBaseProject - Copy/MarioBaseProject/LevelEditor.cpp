#include <SDL.h>
#include "LevelEditor.h"
#include "Constants.h"
#include "Input.h"
#include "EditorMenu.h"
#include "Map.h"
#include "ScreenManager.h"

LevelEditor::LevelEditor(SDL_Renderer* renderer, const std::string& mapName) : BaseLevel(renderer, mapName)
{
	SDL_SetWindowSize(ScreenManager::GetInst()->GetWindow(), SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT);
	SetupLevel();
	tileSelector = new EditorMenu(map);
}

LevelEditor::~LevelEditor()
{
	delete map;
	map = nullptr;

	delete tileSelector;
	tileSelector = nullptr;
}

void LevelEditor::SetupLevel()
{
	map = new Map(currentMapName, true);
}

void LevelEditor::Draw()
{
	BaseLevel::Draw();
	
	if (tileSelector != nullptr)
		tileSelector->Draw();
}

void LevelEditor::Update(float deltaTime)
{
	if (Input::WasKeyDown(Key_K))
	{
		ScreenManager::GetInst()->ChangeScreen(SCREEN_LEVEL, currentMapName);
		return;
	}
	
	if (Input::WasKeyDown(Key_T))
		map->SaveMap(currentMapName);

	if (Input::WasKeyDown(Key_Y))
		map->LoadMap(currentMapName);

	if (Input::WasKeyDown(Key_KP_PLUS))
		map->ChangeLength(map->GetLength() + (10 * TILE_SIZE));

	if (Input::WasKeyDown(Key_KP_MINUS))
		map->ChangeLength(map->GetLength() - (10 * TILE_SIZE));
	
	tileSelector->Update(deltaTime);
}