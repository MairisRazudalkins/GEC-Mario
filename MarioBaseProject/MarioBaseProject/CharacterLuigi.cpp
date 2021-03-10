#include "CharacterLuigi.h"
#include "Input.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPos, LevelMap* map) : BaseCharacter(renderer, imagePath, startPos, map)
{
	
}

void CharacterLuigi::Update(float deltaSeconds, SDL_Event e)
{
	isMovingLeft = Input::IsKeyDown(LEFT) ? true : false;
	isMovingRight = Input::IsKeyDown(RIGHT) ? true : false;

	if (Input::IsKeyDown(UP))
	{
		if (isGrounded)
			Jump(deltaSeconds);
	}

	BaseCharacter::Update(deltaSeconds, e);
}
