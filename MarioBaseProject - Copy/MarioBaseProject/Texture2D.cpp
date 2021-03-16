#include <iostream>
#include <SDL_image.h>
#include "Texture2D.h"
#include "ScreenManager.h"

Texture2D::Texture2D()
{
	this->renderer = ScreenManager::GetInst()->GetRenderer();
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

void Texture2D::DrawToWorld(Vector2D pos, SDL_RendererFlip flip, double angle)
{
	Vector2D cameraPos = ScreenManager::GetInst()->GetCameraPos();
	SDL_Rect renderLoc = { pos.x - cameraPos.x, pos.y - cameraPos.y, width, height };
	
	SDL_RenderCopyEx(renderer, texture, nullptr, &renderLoc, angle, nullptr, flip);
}

void Texture2D::DrawToWorld(Rect2D sourceRect, Rect2D sourceDest, SDL_RendererFlip flip, double angle)
{
	Vector2D cameraPos = ScreenManager::GetInst()->GetCameraPos();
	SDL_Rect srcRect = { sourceRect.x, sourceRect.y, sourceRect.width, sourceRect.height };
	SDL_Rect dstRect = { sourceDest.x - cameraPos.x, sourceDest.y - cameraPos.y, sourceDest.width, sourceDest.height };
	
	SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle, nullptr, flip);
}

void Texture2D::DrawToScreen(Vector2D pos, SDL_RendererFlip flip, double angle) //these draw functions are kinda dumb.
{
	SDL_Rect renderLoc = { pos.x, pos.y, width, height };

	SDL_RenderCopyEx(renderer, texture, nullptr, &renderLoc, angle, nullptr, flip);
}

void Texture2D::DrawToScreen(Rect2D sourceRect, Rect2D sourceDest, SDL_RendererFlip flip, double angle)
{
	SDL_Rect srcRect = { sourceRect.x,sourceRect.y, sourceRect.width, sourceRect.height };
	SDL_Rect dstRect = { sourceDest.x, sourceDest.y, sourceDest.width, sourceDest.height };
	
	SDL_RenderCopyEx(renderer, texture, &srcRect, & dstRect, angle, nullptr, flip);
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
