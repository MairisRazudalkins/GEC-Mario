#include <iostream>
#include <algorithm>
#include "BaseCharacter.h"
#include "Constants.h"
#include "Input.h"
#include "LevelMap.h"

BaseCharacter::BaseCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPos, LevelMap* map)
{
	collisionRadius = 15.f;
	facingDir = DIR_RIGHT;
	position = startPos;
	currentMap = map;
	isGrounded = false;
	isAlive = true;
	
	this->renderer = renderer;
	texture = new Texture2D(renderer);

	if (!texture->LoadTextureFromFile(imagePath))
	{
		std::cout << "Failed to load character texture\n";
		return;
	}

	testTile = new Texture2D(renderer);

	if (!testTile->LoadTextureFromFile("Images/TestTile.png"))
	{
		return;
	}

	//velocity = Vector2D(0, GRAVITY_SCALE);
}

BaseCharacter::~BaseCharacter()
{

}

void BaseCharacter::MoveLeft(float deltaTime)
{
	facingDir = DIR_LEFT;
	position.x -= movementSpeed * deltaTime;
	
	//velocity.x = velocity.x < -300.f ? -300.f : velocity.x - (3 * MOVEMENT_SPEED * deltaTime);
}

void BaseCharacter::MoveRight(float deltaTime)
{
	facingDir = DIR_RIGHT;
	position.x += movementSpeed * deltaTime;
	//velocity.x = velocity.x > 300.f ? 300.f : velocity.x + (3 * MOVEMENT_SPEED * deltaTime);
}

void BaseCharacter::Jump(float deltaTime)
{
	if (!jumping && isGrounded)
	{
		jumpForce = INITIAL_JUMP_FORCE;
		jumping = true;
		canJump = false;
	}
	
	//velocity.y = -200.f;
	//isGrounded = false;
}

void BaseCharacter::AddGravity(float deltaTime)
{
	int footPos = (int)(position.y + texture->GetHeight()) / TILE_HEIGHT;
	int centeralXPos = (int)(position.x + (texture->GetWidth() * 0.5)) / TILE_WIDTH;

	if (currentMap->GetTileAt(footPos, centeralXPos) == 0)
	{
		//currentMap->tiles[]
		
		position.y += GRAVITY_SCALE * deltaTime;
		isGrounded = false;
	}
	else
	{
		canJump = true;
		isGrounded = true;
	}
	
	//velocity = velocity + Vector2D(0, GRAVITY_SCALE) * deltaTime;
}

void BaseCharacter::ApplyPhysics(float deltaTime)
{
	//position = position + velocity * deltaTime;
	//
	//if (!(isMovingLeft || isMovingRight)) 
	//{
	//	if (abs(velocity.x) > 0.1) 
	//		velocity.x -= velocity.x > 0 ? 0.3 : -0.3;
	//	else 
	//		velocity.x = 0;
	//}
	//
	//int centeralXPos = (int)(position.x + (texture->GetWidth() * 0.5)) / TILE_WIDTH;
	//int headPos = (int)(position.y / TILE_HEIGHT);
	//int footPos = (int)(position.y + texture->GetHeight()) / TILE_HEIGHT;
	//
	//testTilePos.x = centeralXPos * TILE_WIDTH;
	//testTilePos.y = headPos * TILE_HEIGHT;
	//
	//isGrounded = velocity.y == 0 ? true : false;
	//
	//if (currentMap->GetTileAt(footPos, centeralXPos) == 0)
	//{
	//	AddGravity(deltaTime);
	//}
	//else
	//{
	//	velocity.y = 0;
	//}
}

void BaseCharacter::Render()
{
	texture->Render(position, facingDir == DIR_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	testTile->Render(testTilePos, SDL_FLIP_NONE);
}

void BaseCharacter::Update(float deltaSeconds, SDL_Event e)
{
	//ApplyPhysics(deltaSeconds);

	int footPos = (int)(position.y + texture->GetHeight()) / TILE_HEIGHT;
	int centeralXPos = (int)(position.x + (texture->GetWidth() * 0.5)) / TILE_WIDTH;
	testTilePos = Vector2D(centeralXPos * 32, footPos * 32);
	
	AddGravity(deltaSeconds);
	
	if (jumping)
	{
		position.y -= jumpForce * deltaSeconds;
		jumpForce -= JUMP_FORCE_DECREMENT * deltaSeconds;

		if (jumpForce <= 0.f)
		{
			jumping = false;
		}
	}

	if (isMovingLeft)
		MoveLeft(deltaSeconds);
	else if (isMovingRight)
		MoveRight(deltaSeconds);
	
	//AddGravity(deltaSeconds);
}

void BaseCharacter::SetPosition(Vector2D newPos)
{
	position = newPos;
}

void BaseCharacter::CancelJump()
{
	jumping = false;
}

void BaseCharacter::ChangeMovementDir(FacingDirection movementDir)
{
	if (movementDir == DIR_RIGHT)
	{
		isMovingRight = true;
		isMovingLeft = false;
	}
	else if (movementDir == DIR_LEFT)
	{
		isMovingRight = false;
		isMovingLeft = true;
	}
}