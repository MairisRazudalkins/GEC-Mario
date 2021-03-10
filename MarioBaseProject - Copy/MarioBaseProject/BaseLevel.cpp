#include <SDL.h>
#include "BaseLevel.h"
#include "Map.h"
#include "Constants.h"

BaseLevel::BaseLevel(SDL_Renderer* renderer, const std::string& mapName)
{
	this->renderer = renderer;
	map = new Map(mapName);
}

BaseLevel::~BaseLevel()
{
	renderer = nullptr;

	delete map;
	map = nullptr;
}

void BaseLevel::Draw()
{
	map->Draw();
}

void BaseLevel::Update(float deltaTime)
{
}

bool BaseLevel::SetupLevel()
{
	return true;
}

int BaseLevel::GetCurMapLength()
{
	return map != nullptr ? map->GetLength() : SCREEN_WIDTH;
}