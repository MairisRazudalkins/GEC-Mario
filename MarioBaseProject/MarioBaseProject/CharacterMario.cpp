#include "CharacterMario.h"

#include "Input.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPos, LevelMap* map) : BaseCharacter(renderer, imagePath, startPos, map)
{
}

void CharacterMario::Update(float deltaSeconds, SDL_Event e)
{
	isMovingLeft = Input::IsKeyDown(A) ? true : false;
	isMovingRight = Input::IsKeyDown(D) ? true : false;

	if (Input::IsKeyDown(SPACE))
	{
		Jump(deltaSeconds);
	}
	
	if (Input::IsKeyDown(W))
	{
		if (isGrounded)
			Jump(deltaSeconds);
	}

	BaseCharacter::Update(deltaSeconds, e);
}
