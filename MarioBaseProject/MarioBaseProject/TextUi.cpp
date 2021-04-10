#include "TextUi.h"
#include "ScreenManager.h"

TTF_Font* TextUi::globalFont = nullptr;

TextUi::TextUi(Vector2D position, SDL_Color color, std::string text) : GameObject()
{
	this->textPosition = position;
	this->color = color;
	this->text = text;

	textTexture = SDL_CreateTextureFromSurface(ScreenManager::GetInst()->GetRenderer(), GetTextSurface());
}

TextUi::~TextUi()
{
	if (globalFont != nullptr)
	{
		TTF_CloseFont(globalFont);
		globalFont = nullptr;
	}

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

void TextUi::Draw()
{
	SDL_Rect srcRect = { 0, 0, textSurface->w, textSurface->h };
	SDL_Rect destRect = { textPosition.x, textPosition.y, textSurface->w, textSurface->h };
	
	SDL_RenderCopy(ScreenManager::GetInst()->GetRenderer(), textTexture, &srcRect, &destRect);
}

void TextUi::ChangeText(std::string text)
{
	this->text = text;
	SDL_DestroyTexture(textTexture);
	textTexture = nullptr;
	SDL_FreeSurface(textSurface); 
	textSurface = nullptr;
	textTexture = SDL_CreateTextureFromSurface(ScreenManager::GetInst()->GetRenderer(), GetTextSurface());
}