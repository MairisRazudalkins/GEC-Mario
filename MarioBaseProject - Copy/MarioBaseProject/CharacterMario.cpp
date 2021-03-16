#include "CharacterMario.h"
#include "Input.h"
#include "Texture2D.h"
#include "Constants.h"

CharacterMario::CharacterMario(Vector2D position, std::string path, Map* map) : Character(position, path, map)
{
	objTag = "Mario";
	SetSrcRect(Rect2D(0.f, 0.f, TILE_SIZE, TILE_SIZE));
}

CharacterMario::~CharacterMario()
{
	
}

void CharacterMario::Update(float deltaTime)
{
	isMovingLeft = Input::IsKeyHeld(Key_A) || Input::IsKeyHeld(Key_LEFT) ? true : false;
	isMovingRight = Input::IsKeyHeld(Key_D) || Input::IsKeyHeld(Key_RIGHT) ? true : false;

	if (Input::IsKeyHeld(Key_SPACE) || Input::IsKeyHeld(Key_UP))
		Jump();

	Character::Update(deltaTime);
}

void CharacterMario::GivePowerUp(PowerUpType powerUpType)
{
	
}