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
	Texture2D();
	~Texture2D();

	void Free();
	void DrawToWorld(Vector2D pos, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.f);
	void DrawToWorld(Rect2D sourceRect, Rect2D sourceDest, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.f);
	void DrawToScreen(Vector2D pos, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.f);
	void DrawToScreen(Rect2D sourceRect, Rect2D sourceDest, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.f);
	bool LoadTextureFromFile(std::string path);

	int GetWidth() { return width; }
	int GetHeight() { return height; }
};

#endif