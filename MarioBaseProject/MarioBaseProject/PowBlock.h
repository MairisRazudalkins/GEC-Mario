#pragma once
#include <SDL.h>
#include "Commons.h"

class LevelMap;
class Texture2D;

class PowBlock
{
	SDL_Renderer* renderer;
	Vector2D position;
	Texture2D* texture;
	LevelMap* levelMap;

	float singleSpriteWidth;
	float singleSpriteHeight;
	int numOfHitsLeft;
	
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	void Render();
	void TakeHit();
	Rect2D GetCollisionBox() { return Rect2D(position.x, position.y, singleSpriteWidth, singleSpriteHeight); }
	bool IsAvaliable(){ return numOfHitsLeft >= 0; }
};