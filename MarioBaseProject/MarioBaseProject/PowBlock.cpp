#include <iostream>
#include <SDL.h>
#include "PowBlock.h"
#include "LevelMap.h"
#include "Constants.h"
#include "Texture2D.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/PowBlock.png";
	this->renderer = renderer;
	texture = new Texture2D(this->renderer);

	if (!texture->LoadTextureFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture\n";
		return;
	}

	levelMap = map;
	singleSpriteWidth = texture->GetWidth() / 3;
	singleSpriteHeight = texture->GetHeight();
	numOfHitsLeft = 2;
	position = Vector2D((SCREEN_WIDTH * 0.5f) - singleSpriteWidth * 0.5f, 360);
}

PowBlock::~PowBlock()
{
	renderer = nullptr;
	levelMap = nullptr;

	delete texture;
	texture = nullptr;
}

void PowBlock::Render()
{
	if (numOfHitsLeft >= 0)
	{
		SDL_Rect src = { singleSpriteWidth * numOfHitsLeft, 0, singleSpriteWidth, singleSpriteHeight }; // position on sprite sheet
		SDL_Rect dst = { position.x, position.y, singleSpriteWidth, singleSpriteHeight }; // position in level
		texture->Render(src, dst, SDL_RendererFlip::SDL_FLIP_NONE, 0.f);
	}
	
}

void PowBlock::TakeHit()
{
	numOfHitsLeft--;
	std::cout << numOfHitsLeft << std::endl;

	if (numOfHitsLeft <= 0)
	{
		levelMap->ChangeTileAt(8, 7, 0);
		levelMap->ChangeTileAt(8, 8, 0);
	}

	//std::cout << numOfHitsLeft;
}