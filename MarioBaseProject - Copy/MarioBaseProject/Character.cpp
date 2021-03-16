#include "Character.h"

#include <iostream>

#include "Constants.h"
#include "Utility.h"
#include "ScreenManager.h"
#include "Map.h"

Character::Character(Vector2D position, std::string path, Map* map) : SceneObject(position, path)
{
	objTag = "Character";
	this->map = map;

	testTile = new Texture2D();
	testTile->LoadTextureFromFile("Images/TestTile.png");
}

Character::~Character()
{
	map = nullptr;

	testTile->Free();
}

void Character::Draw()
{
	texture->DrawToWorld(GetSrcRect(), Rect2D(position.x, position.y, srcRect.width, srcRect.height), facingDir == DIR_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
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
}

void Character::KillCharacter()
{
	isAlive = false;
}

void Character::MoveLeft(float deltaTime)
{
	facingDir = DIR_LEFT;
	movement = Utils::Clamp(movement - (isGrounded ? accelerationRate : airControl) * deltaTime, -1.f, 1.f);
}

void Character::MoveRight(float deltaTime)
{
	facingDir = DIR_RIGHT;
	movement = Utils::Clamp(movement + (isGrounded ? accelerationRate : airControl) * deltaTime, -1.f, 1.f);
}

void Character::Decelerate(float deltaTime)
{
	if (movement > 0.f)
		movement = Utils::Clamp(movement - (friction * deltaTime), 0.f, movement);
	else if (movement < 0.f)
		movement = Utils::Clamp(movement + (friction * deltaTime), movement, 0.f);
}

void Character::ApplyPhysics(float deltaTime)
{
	velocity.x = movement * movementSpeed * deltaTime;
	
	if (!isGrounded)
		velocity.y = (double)Utils::Clamp(velocity.y + (GRAVITY_DECREASE_RATE * deltaTime), velocity.y, GRAVITY_MAX_FALL_SPEED);

	position += velocity;
	CheckCollision();
}

void Character::CheckCollision()	
{
	int centerXPos = (int)(position.x + (GetSrcRect().width / 2)) / TILE_SIZE;
	int centerYPos = (int)(position.y + (GetSrcRect().height / 2)) / TILE_SIZE;

	SceneObject* objAtHead = map->GetTileAt(centerXPos, (int)(position.y) / TILE_SIZE);
	SceneObject* objAtFoot = map->GetTileAt(centerXPos, (int)(position.y + GetSrcRect().height) / TILE_SIZE);
	SceneObject* objAtDir = map->GetTileAt(facingDir == DIR_RIGHT ? (int)(position.x + GetSrcRect().width) / TILE_SIZE :  (int)(position.x) / TILE_SIZE, centerYPos);

	isGrounded = false;
	
	if (objAtHead != nullptr && (objAtHead->GetCollisionType() == BLOCK) && velocity.y < 0.f)
	{
		velocity.y = GRAVITY_MAX_FALL_SPEED;
		objAtHead->OnObjectHit(this);
	}
	
	if (objAtFoot != nullptr && (objAtFoot->GetCollisionType() == BLOCK || (objAtFoot->GetCollisionType() == PLATFORM && velocity.y >= 0.f) ))
	{
		velocity.y = 0.f;
		position.y = objAtFoot->GetPosition().y - GetSrcRect().height;
		isGrounded = true;
	}
	
	if (objAtDir != nullptr && (objAtDir->GetCollisionType() == BLOCK && position.x + srcRect.width >= objAtDir->GetPosition().x))
	{
		position.x = facingDir == DIR_RIGHT ? objAtDir->GetPosition().x - GetSrcRect().width : objAtDir->GetPosition().x + GetSrcRect().width;
		movement = 0.f;
	}
	
	if (position.x <= ScreenManager::GetInst()->GetCameraPos().x)
	{
		position.x = ScreenManager::GetInst()->GetCameraPos().x;
		movement = 0.f;
	}
	else if (position.x + srcRect.width >= ScreenManager::GetInst()->GetCurrentMapLength()) // replace with level length
	{
		position.x = ScreenManager::GetInst()->GetCurrentMapLength() - srcRect.width;
		movement = 0.f;
	}
}

void Character::Jump()
{
	if (isGrounded)
	{
		velocity.y = initialJumpVelocity;
		isGrounded = false;
	}
}
