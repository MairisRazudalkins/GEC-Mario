#include "CharacterMario.h"
#include "Input.h"
#include "Constants.h"
#include "Texture2D.h"

CharacterMario::CharacterMario(Vector2D position, std::string path, Map* map) : Character(position, path, map)
{
	
}

CharacterMario::~CharacterMario()
{
}

void CharacterMario::Update(float deltaTime)
{
	ApplyPhysics(deltaTime);

	isMovingLeft = Input::IsKeyHeld(Key_A) ? true : false;
	isMovingRight = Input::IsKeyHeld(Key_D) ? true : false;

	if (Input::IsKeyHeld(Key_SPACE))
	{
		Jump();
	}

	Character::Update(deltaTime);
}

void CharacterMario::Draw()
{
	Character::Draw();
}

void CharacterMario::ApplyPhysics(float deltaTime)
{
	Character::ApplyPhysics(deltaTime);
}