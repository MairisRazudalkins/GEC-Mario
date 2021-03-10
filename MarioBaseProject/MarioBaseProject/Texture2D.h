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
	Texture2D() {};
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	void Free();
	void Render(Vector2D pos, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0);
	void Render(SDL_Rect sourceRect, SDL_Rect sourceDest, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.f);
	bool LoadTextureFromFile(std::string path);

	int GetWidth() { return width; }
	int GetHeight() { return height; }
};

#endif
