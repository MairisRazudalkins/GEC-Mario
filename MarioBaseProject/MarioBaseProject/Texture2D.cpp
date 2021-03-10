#include "Texture2D.h"
#include <iostream>
#include <SDL_image.h>

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

Texture2D::~Texture2D()
{
	Free();
	renderer = nullptr;
}

void Texture2D::Free()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;

		width = 0;
		height = 0;
	}
}

void Texture2D::Render(Vector2D pos, SDL_RendererFlip flip, double angle)
{
	SDL_Rect renderLoc = { pos.x,pos.y, width, height };
	SDL_RenderCopyEx(renderer, texture, nullptr, &renderLoc, 0, nullptr, flip);
}

void Texture2D::Render(SDL_Rect sourceRect, SDL_Rect sourceDest, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(renderer, texture, &sourceRect, &sourceDest, angle, nullptr, flip);
}

bool Texture2D::LoadTextureFromFile(std::string path)
{
	Free();
	
	SDL_Surface* newSurface = IMG_Load(path.c_str());

	if (newSurface != nullptr)
	{
		SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 0, 0xFF, 0xFF));
		texture = SDL_CreateTextureFromSurface(renderer, newSurface);

		if (texture == nullptr)
		{
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}

		width = newSurface->w;
		height = newSurface->h;
		
		SDL_FreeSurface(newSurface);
	}
	else
	{
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}

	return texture != nullptr;
}
