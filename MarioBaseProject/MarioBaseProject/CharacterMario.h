#pragma once
#include "BaseCharacter.h"
class CharacterMario : public BaseCharacter
{

public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPos, LevelMap* map);
	void Update(float deltaSeconds, SDL_Event e) override;
};

