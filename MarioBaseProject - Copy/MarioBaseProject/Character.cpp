#include "Character.h"
#include "Constants.h"
#include "Utility.h"
#include "ScreenManager.h"
#include "Map.h"

#include <iostream>

Character::Character(Vector2D position, std::string path, Map* map, float movementSpeed, float mass, float accelerationRate) : SceneObject(position, path), movementSpeed(movementSpeed), mass(mass), accelerationRate(accelerationRate)
{
	objTag = "Character";
	this->map = map;
}

Character::~Character()
{
	map = nullptr;
}

void Character::Draw()
{
	texture->DrawToWorld(GetSrcRect(), Rect2D(position.x, position.y, srcRect.width, srcRect.height), flip);
}

void Character::Update(float deltaTime)
{
	if (!isAlive)
		return;
	
	if (deltaTime == 0.f)
		deltaTime = 0.001f;
	
	if (isMovingRight)
		MoveRight(deltaTime);
	else if (isMovingLeft)
		MoveLeft(deltaTime);
	else
		movement = 0.f;
	
	ApplyPhysics(deltaTime);

	if (position.y > SCREEN_HEIGHT)
		KillCharacter();
}

void Character::KillCharacter()
{
	isAlive = false;
}

void Character::MoveLeft(float deltaTime)
{
	facingDir = DIR_LEFT;
	flip = SDL_FLIP_HORIZONTAL;
	movement = -1.f;
}

void Character::MoveRight(float deltaTime)
{
	facingDir = DIR_RIGHT;
	flip = SDL_FLIP_NONE;
	movement = 1.f;
}

float Character::Decelerate()
{
	//acceleration.x - (friction / mass);
	
	if (acceleration.x > 0.f)
		acceleration.x = Utils::Clamp(acceleration.x - (friction / mass), 0.f, acceleration.x);
	else if (acceleration.x < 0.f)
		acceleration.x = Utils::Clamp(acceleration.x + (friction / mass), acceleration.x, 0.f);

	return acceleration.x;
}

void Character::ApplyPhysics(float deltaTime)
{
	acceleration.x = Utils::Clamp( movement == 0.f ? Decelerate() :  acceleration.x + ((movement * (isGrounded ? accelerationRate : airControl)) / mass), -1.f, 1.f);
	acceleration.y = Utils::Clamp(acceleration.y + (GRAVITY_RATE / mass), acceleration.y + (GRAVITY_RATE / mass), GRAVITY_MAX);

	velocity.x = ((acceleration.x / mass) * movementSpeed) * deltaTime;
	velocity.y = Utils::Clamp(acceleration.y * deltaTime, acceleration.y * deltaTime, GRAVITY_MAX);

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
		acceleration.y = GRAVITY_MAX;
		objAtHead->OnObjectHit(this);
	}
	
	if (objAtFoot != nullptr && (objAtFoot->GetCollisionType() == BLOCK || (objAtFoot->GetCollisionType() == PLATFORM && acceleration.y >= 0.f) ))
	{
		velocity.y = 0.f;
		position.y = objAtFoot->GetPosition().y - GetSrcRect().height;
		isGrounded = true;
	}
	
	if (objAtDir != nullptr && (objAtDir->GetCollisionType() == BLOCK && position.x + srcRect.width >= objAtDir->GetPosition().x))
	{
		position.x = facingDir == DIR_RIGHT ? objAtDir->GetPosition().x - GetSrcRect().width : objAtDir->GetPosition().x + GetSrcRect().width;
		acceleration.x = 0.f;
	}
}

void Character::Jump()
{
	if (isGrounded)
	{
		acceleration.y = initialJumpVelocity;
		isGrounded = false;
	}
}
