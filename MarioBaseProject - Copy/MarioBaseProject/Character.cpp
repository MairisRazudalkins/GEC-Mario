#include "Character.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Utility.h"
#include "ScreenManager.h"
#include "Map.h"

Character::Character(Vector2D position, std::string path, Map* map) : SceneObject(position, path)
{
	this->map = map;
}

Character::~Character()
{
	
}

void Character::Draw()
{
	texture->DrawToWorld(Rect2D(0, 0, texture->GetWidth(), texture->GetHeight()), Rect2D(position.x, position.y, texture->GetWidth(), texture->GetHeight()), facingDir == DIR_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	//texture->Render(position, facingDir == DIR_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Character::Update(float deltaTime)
{
	if (isMovingRight)
		MoveRight(deltaTime);
	else if (isMovingLeft)
		MoveLeft(deltaTime);
	else if (isGrounded)
		Decelerate(deltaTime);
	
	ApplyPhysics(deltaTime);
	CheckCollision();
}

void Character::MoveLeft(float deltaTime)
{
	facingDir = DIR_LEFT;
	movement = Utils::Clamp(movement - (isGrounded ? accelerationRate : airControl), -1.f, 1.f);
}

void Character::MoveRight(float deltaTime)
{
	facingDir = DIR_RIGHT;
	movement = Utils::Clamp(movement + (isGrounded ? accelerationRate : airControl), -1.f, 1.f);
}

void Character::Decelerate(float deltaTime)
{
	if (movement > 0.f)
		movement = Utils::Clamp(movement - friction, 0.f, movement);
	else if (movement < 0.f)
		movement = Utils::Clamp(movement + friction, movement, 0.f);
}

void Character::ApplyPhysics(float deltaTime)
{
	velocity.x = movement * movementSpeed * deltaTime;
	velocity.y = GRAVITY_RATE * deltaTime;

	if (!isGrounded)
	{
		if (jumpForce <= 0.f)
		{
			velocity.y = GRAVITY_RATE * deltaTime;
		}
		else
		{
			jumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
			velocity.y -= jumpForce * deltaTime;
		}
	}
	
	// add gravity
	// add collision detection

	position += velocity;
}

void Character::CheckCollision()	
{
	int footPos = (int)(position.y + texture->GetHeight()) / TILE_SIZE;
	int centeralXPos = (int)(position.x + (texture->GetWidth() * 0.5)) / TILE_SIZE;
	
	if (position.y >= 400.f)
	{
		position.y = 400.f;
		isGrounded = true;
	}

	if (position.x <= ScreenManager::GetCameraPos().x)
	{
		position.x = ScreenManager::GetCameraPos().x;
		movement = 0.f;
	}
	else if (position.x + texture->GetWidth() >= ScreenManager::GetCurrentMapLength() * TILE_SIZE) // replace with level length
	{
		position.x = (ScreenManager::GetCurrentMapLength() * TILE_SIZE) - texture->GetWidth();
		movement = 0.f;
	}
}

void Character::Jump()
{
	if (isGrounded)
	{
		jumpForce = INITIAL_JUMP_FORCE;
		isGrounded = false;
	}
}
