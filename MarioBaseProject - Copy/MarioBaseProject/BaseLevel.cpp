#include <SDL.h>
#include "BaseLevel.h"
#include "Map.h"
#include "Constants.h"

BaseLevel::BaseLevel(SDL_Renderer* renderer, const std::string& mapName)
{
	this->renderer = renderer;
	currentMapName = mapName;
}

BaseLevel::~BaseLevel()
{
	renderer = nullptr;
	
	delete map;
	map = nullptr;
}

void BaseLevel::Draw()
{
	if (map)
		map->Draw();
}

void BaseLevel::Update(float deltaTime)
{
}

void BaseLevel::SetupLevel()
{
	map = new Map(currentMapName);
}

int BaseLevel::GetCurMapLength()
{
	return map != nullptr ? map->GetLength() : SCREEN_WIDTH;
}

bool BaseLevel::GetIsEditor()
{
	return map->isEditing;
}