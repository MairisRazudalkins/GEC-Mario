#pragma once
#include "SceneObject.h"
#include <SDL_ttf.h>

class TextUi : public GameObject
{
	static TTF_Font* globalFont;
	
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;

	Vector2D textPosition;

	SDL_Color color;
	std::string text;

	float timer = 0.f;
	
public:
	TextUi(Vector2D position, SDL_Color color, std::string text);
	~TextUi();
	void Draw() override;
	void Update(float deltaTime) override {};

	static TTF_Font* GetGlobalFont() { return globalFont != nullptr ? globalFont : globalFont = TTF_OpenFont("Fonts/Super-Mario-Bros-3.ttf", 15); }
	SDL_Surface* GetTextSurface() { return textSurface != nullptr ? textSurface : textSurface = TTF_RenderText_Solid(GetGlobalFont(), text.c_str(), color); }
	void ChangeText(std::string text);
};