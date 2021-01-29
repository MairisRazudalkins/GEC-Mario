#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include <SDL.h>
#include <string>
#include "Commons.h"

class Texture2D
{
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	int width;
	int height;

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	void Free();
	void Render(Vector2D pos, SDL_RendererFlip flip, double angle = 0.0);
	bool LoadTextureFromFile(std::string path);

	int GetWidth() { return width; }
	int GetHeight() { return height; }
};

#endif
